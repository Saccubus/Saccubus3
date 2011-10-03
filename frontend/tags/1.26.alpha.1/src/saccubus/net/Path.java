package saccubus.net;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * <p>
 * �^�C�g��: ������΂�
 * </p>
 *
 * <p>
 * ����: �j�R�j�R����̓�����R�����g���ŕۑ�
 * </p>
 *
 * @version 1.22r3e
 * @author orz
 *
 */
public class Path extends File{
	static final long serialVersionUID = 1L;

	Path(String path){
		super(path);
		// ���Ӂ@path�����΃p�X���ł���΃p�X���ł��Ȃ�����
		// �J�����g�f�B���N�g���ɂ���t�@�C�����Ӗ�����
	}
	Path(File file){
		super(file.getAbsolutePath());
	}
	Path(File dir, String name){
		super(dir, name);
	}
	Path(Path dirPath, String name){
		super(dirPath, name);
	}

//	@Override
//	public String getName(){
//		return super.getName();
//	}
	/**
	 * static getName(String)
	 * @param name : full path name of file : String
	 * @return last name of file : String
	 */
//	public static String getName(String name){
//		File path = new File(name);
//		return path.getName();
//	}
	/**
	 * alias of static getName(String)
	 * @param fullname : full path name of file : String
	 * @return last name of file : String
	 */
//	public static String getFileName(String fullname){
//		return getName(fullname);
//	}
	/**
	 * alias of getAbsolutePath()
	 * @return
	 */
	private String getFullName(){
		return getAbsolutePath();
	}
	/**
	 * @return Full Path Name of Parent : String
	 */
//	@Override
//	public String getParent(){
//		return super.getParent();
//	}
	/**
	 *
	 * @return Full Path of Parent : Path
	 */
//	public Path getParentPath(){
//		return new Path(getParent());
//	}
//	@Override
//	public boolean isDirectory(){
//		return file.isDirectory();
//	}
//	@Override
//	public boolean isFile(){
//		return file.isFile();
//	}
//	public String[] list(){
//		return file.list();
//	}
	/**
	 * static list of dir, returns full path name array<br/>
	 * NOT alias as (new Path(dir)).list()<br/>
	 * @param dir : Name of directory : String
	 * @return Full filenames of child dirs or child files : Array of String
	 */
	public static String[] getFiullnameList(String dir){
		File path = new File(dir);
		String[] lists = path.list();
		int l = lists.length;
		String[] fulls = new String[l];
		for (int i = 0; i < l; i++){
			fulls[i] = new File(path, lists[i]).getAbsolutePath();
		}
		return fulls;
	}
	/**
	 * static exists(String)
	 */
//	public static boolean exists(String name){
//		Path path = new Path(name);
//		return path.exists();
//	}
//	/**
//	 * @return Child directorys or child files : Array of File
//	 */
//	public File[] listFiles(){
//		return file.listFiles();
//	}
	/**
	 * @return Child directories or child files : Array of Path
	 */
	public Path[] listPath(){
		String[] lists = list();
		int l = lists.length;
		Path[] paths = new Path[l];
		for (int i = 0; i < l; i++){
			paths[i] = new Path(this, lists[i]);
		}
		return paths;
	}
	/**
	 * static String[] list(String)
	 * @param dir : name of parent, must be full path : String
	 * @return Childs of dir : Array of String
	 */
	public static String[] list(String dir){
		Path path = new Path(dir);
		return path.list();
	}
	/**
	 * static String[] list(path)
	 * @param path : Path of parent : Path
	 * @return Childs of path : Array of String
	 */
	public static String[] list(Path path){
		return path.list();
	}
	/**
	 * static File[] listFiles(dir)
	 * @param dir : Name of parent : String
	 * @return Childs of dir : Array of File
	 */
//	private static File[] listFiles(String dir){
//		Path path = new Path(dir);
//		return path.listFiles();
//	}
	/**
	 * static File[] listFiles(path)
	 * @param path : Path of parent : Path
	 * @return Childs of path : Array of File
	 */
//	private static File[] listFiles(Path path){
//		return path.listFiles();
//	}
	/**
	 * static Path[] listPath(dir)
	 * @param dir : Name of parent : String
	 * @return Childs of dir : Array of Path
	 */
	public static Path[] listPath(String dir){
		Path path = new Path(dir);
		return path.listPath();
	}
	/**
	 * static isDirectory(String str)
	 * @param str : Name of dir or file : String
	 * @return true if str is a directory
	 */
	public static boolean isDirectory(String str){
		Path path = new Path(str);
		return path.isDirectory();
	}
	/**
	 * static isFile(String str)
	 * @param str : Name of dir or file : String
	 * @return true if str is a normal file
	 */
	public static boolean isFile(String str){
		Path path = new Path(str);
		return path.isFile();
	}
	/**
	 * search file name of childs
	 * @param name : target file name, not contains directory path: String
	 * @return String : Full name of found file/directory, if name is child name
	 *                  "" empty string if not found
	 */
	public String search(String name){
		Path[] childs = this.listPath();
		//Path namePath = new Path(name); ��NG
		for (Path p : childs){
			if (p.getName().equals(name)){
				return p.getAbsolutePath();		// means p.getFullName()
			}
		}
		return "";
	}
	/**
	 * static search file name of childs
	 * @param dir : parent file name : String
	 * @param name : target file name, not contains directory path: String
	 * @return String : Full name of found file/directory, if name is child name
	 *                  "" empty string if not found
	 */
	public static String search(String dir, String name){
		Path dirPath = new Path(dir);
		return dirPath.search(name);
	}
	/**
	 * static search file name of childs: ANOTHER IMPLEMENTATION
	 * @param dir : parent file name : String
	 * @param name : target file name, not contains directory path: String
	 * @return String : Full name of found file/directory, if name is child name
	 *                  "" empty string if not found
	 */
	public static String searchFile(String dir, String name){
		File dirFile = new File(dir);
		String[] childs = dirFile.list();
		for (String s : childs){
			if (s.equals(name)){
				// return new File(dirFile, name).getAbsolutePath();
				return dir + File.separator + name;
			}
		}
		return "";
	}
	/**
	 * index of string in the last name of Path, i.e. path.getName()
	 * @param str : search key string
	 * @return index of str, -1 if not found
	 */
	public int indexOf(String str){
		String name = getName();
		return name.indexOf(str);
	}
	/**
	 * whether contains key string in the last name of Path, i.e. path.getName()
	 * @param str : search key string
	 * @return true if last name of path contains key string : boolean
	 */
	public boolean contains(String str){
		return indexOf(str) >= 0;
	}
	/**
	 * search file name conteins key string among childs
	 * @param key : target key : String
	 * @return String : Full name of found file/directory, if that child name contains key
	 *                  "" empty string if not found
	 */
	public String searchContains(String key){
		String[] childs = list();
		for (String s : childs){
			if (s.indexOf(key) >= 0){
				return new Path(this, s).getFullName();		// i.e. p.getFullName()
			}
		}
		return "";
	}
	/**
	 * static search file name conteins key string among childs
	 * @param dir : parent file full path name : String
	 * @param key : target key : String
	 * @return String : Full name of found file/directory, if that child name contains key
	 *                  "" empty string if not found
	 */
	public static String searchContains(String dir, String key){
		Path path = new Path(dir);
		return path.searchContains(key);
	}
	/**
	 * @see java.io.File#equals(java.lang.Object)
	 */
//	public boolean equals(Object obj){
//		if (!obj.getClass().equals(this.getClass())){
//			return false;
//		}
//		return this.of().equals(((Path)obj).of());
//	}
	/**
	 * Read all text from file and return String with Encoding
	 */
	public static String readAllText(String file, String encoding) {
		BufferedReader br = null;
		try {
			br = new BufferedReader(new InputStreamReader(
					new FileInputStream(file), encoding));
			StringBuffer sb = new StringBuffer();
			String str = null;
			while ((str = br.readLine()) != null){
				sb.append(str + "\n");
			}
			return sb.substring(0);
		} catch (IOException e) {
			e.printStackTrace();
			return "";
		} finally {
			if (br != null) {
				try { br.close(); }
				catch (IOException e) { }
			}
		}
	}
	/**
	 *
	 * @param string   filename
	 * @param app_dir  directory name
	 * @return String : fullname of found file,<br/>
	 *  "" empty string if not found
	 */
	public static String sSearchFile(String string, String app_dir) {
		return search(app_dir, string);
	}

	public String getRelativePath(){
		return getAbsolutePath().replace(new Path("").getAbsolutePath(), ".");
	}
	public String replace(String old, String rep){
		return getRelativePath().replace(old, rep);
	}
	public String getUnixPath(){
		return replace(File.separator, "/");
	}
	public static String toUnixPath(String path){
		return new Path(path).getUnixPath();
	}
	public static String toUnixPath(File file){
		return new Path(file).getUnixPath();
	}
	public static Path mkTemp(String string) {
		File dir = new File("temp");
		if (dir.mkdir()){
			System.out.println("Created directory: temp");
		}
		if (!dir.isDirectory()){
			System.out.println("Can't make directory: temp");
			dir = new File("");
		}
		return new Path(dir, string);
	}
}