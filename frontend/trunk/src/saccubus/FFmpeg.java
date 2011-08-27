package saccubus;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.swing.JLabel;

import saccubus.util.BitReader;
import saccubus.util.Cws2Fws;
import saccubus.util.Stopwatch;

public class FFmpeg {

	private final String exePath;
	private StringBuffer sb;
	private String LastFrame = "";
	private String LastError = "エラー情報がありません";

	public FFmpeg(String path) {
		exePath = path.replace("\\", "/");
	}

	public void setCmd(String string) {
		sb = new StringBuffer();
		sb.append("\"");
		sb.append(exePath);
		sb.append("\" ");
		sb.append(string);
	}

	public void addCmd(String string) {
		sb.append(string);
	}

	public void addFile(File file) {
		String path = file.getPath().replace("\\", "/");
		if (path.indexOf(' ') >= 0 || path.indexOf("　") >= 0){
			sb.append(" \"");
			sb.append(path);
			sb.append("\"");
		} else {
			sb.append(path);
		}
	}

	public String getCmd() {
		return sb.substring(0);
	}

	public interface CallbackInterface extends Callback {
		public boolean checkStop();
		public void doAbort(String text);
	}

	public int exec(int abortedCode, CallbackInterface callback) {
		Process process = null;
		BufferedReader ebr = null;
		try {
		//	System.out.println("\n\n----\nProcessing FFmpeg...\n----\n\n");
			process = Runtime.getRuntime().exec(getCmd());
			ebr = new BufferedReader(new InputStreamReader(process.getErrorStream()));
			String e;
			while ((e = ebr.readLine()) != null) {
				callback.doEveryLoop(e);
				//Stopwatch.show();				// must be set in callback.doEveryLoop
				if (callback.checkStop()) {
					process.destroy();
					callback.doAbort(e);
					return abortedCode;
				}
			}
			process.waitFor();
			return process.exitValue();
		} catch (InterruptedException ex) {
			ex.printStackTrace();
			return -1;
		} catch (IOException ex) {
			ex.printStackTrace();
			return -1;
		} finally {
			try {
				ebr.close();
				process.getErrorStream().close();
			} catch(Exception ex){
				ex.printStackTrace();
			}
		}
	}

	public int exec(JLabel status, int abortedCode, ConvertStopFlag flag, Stopwatch watch) {

		class FFmpegCallback implements CallbackInterface {
			private JLabel status;
			private ConvertStopFlag flag;
			private Stopwatch stopwatch;

			public FFmpegCallback(JLabel status, ConvertStopFlag flag, Stopwatch watch){
				this.status = status;
				this.flag = flag;
				stopwatch = watch;
			}
			@Override
			public boolean checkStop() {
				return flag.needStop();
			}
			@Override
			public void doAbort(String e) {
				status.setText("ffmpegの実行を中止しました。");
			}
			@Override
			public void doEveryLoop(String e) {
				stopwatch.show();
				if (e.startsWith("frame=")) { //
					LastFrame = e;
					status.setText(e);
				} else {
					LastError = e;
					if(!e.endsWith("No accelerated colorspace conversion found")){
						System.out.println(e);
					}
				}
			}
		}

		LastError = "エラー情報がありません";
		LastFrame = "";
		System.out.println("\n\n----\nProcessing FFmpeg...\n----\n\n");
		return exec(abortedCode, new FFmpegCallback(status, flag, watch));
	}

	public String getLastFrame() {
		return LastFrame;
	}

	public String getLastError() {
		return LastError;
	}

	public interface Callback {
		void doEveryLoop(String e);
	}

	/**
	 * ffmpeg を実行する　アボート出来ない。
	 * @param callback
	 * @return
	 */
	public int exec(Callback callback){

		Process process = null;
		BufferedReader ebr = null;
		try {
			process = Runtime.getRuntime().exec(getCmd());
			ebr = new BufferedReader(new InputStreamReader(process.getErrorStream()));
			String e;
			while ((e = ebr.readLine()) != null) {
				callback.doEveryLoop(e);
			}
			process.waitFor();
			return process.exitValue();
		} catch (InterruptedException ex) {
			ex.printStackTrace();
			return -1;
		} catch (IOException ex) {
			ex.printStackTrace();
			return -1;
		} finally {
			try {
				ebr.close();
				process.getErrorStream().close();
			} catch(Exception ex){
				ex.printStackTrace();
			}
		}
	}

	public Aspect getAspect(File videoFile) {
		final StringBuffer output = new StringBuffer();

		class GetAspectCallback implements Callback {
			@Override
			public void doEveryLoop(String e) {
				if (e.indexOf("Video:") >= 0) {
					System.out.println(" " + e.trim());
					output.append(e.trim() + "\n");
				}
			}
		}

		long width;
		long height;
		if (Cws2Fws.isFws(videoFile)){	// swf, maybe NMM
			FileInputStream fis = null;
			try {
				fis = new FileInputStream(videoFile);
				BitReader br = new BitReader(fis);
				int bit = (int)br.readBit(32);	// "FWS" + version, dummy
					bit = (int)br.readBit(32);	// file size, dummy
					bit = (int)br.readBit(5);	// RECT bits spec
				width =	 br.readBit(bit);		// xmin is 0
				width =  br.readBit(bit);		// xmax is width
				width /= 20;	// From swip to pixel
				height = br.readBit(bit);		// ymin is 0
				height = br.readBit(bit);		// ymax is height
				height /= 20;	// From swip to pixel
			} catch (IOException e) {
				e.printStackTrace();
				return null;
			} finally {
				if (fis != null){
					try {
						fis.close();
					} catch (IOException e) { }
				}
			}
		} else {
			// check by ffmpeg
			// ffmpeg.exe -y -i file
			setCmd("-y -i ");
			addFile(videoFile);
			System.out.println("get aspect: " + getCmd());
			exec(new GetAspectCallback());
			String src = output.toString();
			src = src.replaceAll("[^0-9x]", "_");
			String[] list = src.split("_+");
			src = "1x1";	// prevent Exception
			for (String s : list){
				if (s.indexOf('x') > 0){
					src = s;
					break;
				}
			}
			list = src.split("x");
			try {
				width = Long.parseLong(list[0]);
				height = Long.parseLong(list[1]);
			} catch(NumberFormatException e){
				e.printStackTrace();
				return null;
			}
		}
		Aspect asp = new Aspect((int)width, (int)height);
		System.out.println(asp.explain());
		return asp;
	}
//	public enum Aspect {
//		NORMAL, WIDE,
//	}
	public static class Aspect {
		private final int width;
		private final int height;
		private final double aspect;
		public int getWidth() { return width; }
		public int getHeight() { return height; }
		public double getValue() { return aspect; }
		public Aspect(int x, int y){
			width = x;
			height = y;
			if ( y != 0){
				aspect = (double)x / (double)y;
			} else {
				aspect = 0.0;
			}
		}
		public boolean isWide(){
			if (aspect >= 1.700) {
				return true;
			} else {
				return false;
			}
		}
		public String explain(){
			return "(" + width + "x" + height + ")" + String.format("%.3f", aspect);
		}
		public static final Aspect NORMAL = new Aspect(4, 3);
		public static final Aspect WIDE = new Aspect(16, 9);
	}
}
