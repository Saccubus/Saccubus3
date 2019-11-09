/* 

    SDL_rotozoom - test program 

    Copyright (C) A. Schiffler, July 2001

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL.h"
#include "SDL_rotozoom.h"

void
HandleEvent ()
{
  SDL_Event event;

  /* Check for events */
  while (SDL_PollEvent (&event))
    {
      switch (event.type)
	{
	case SDL_KEYDOWN:
	case SDL_QUIT:
	  exit (0);
	  break;
	}
    }
}

void
ClearScreen (SDL_Surface * screen)
{
  int i;
  /* Set the screen to black */
  if (SDL_LockSurface (screen) == 0)
    {
      Uint32 black;
      Uint8 *pixels;
      black = SDL_MapRGB (screen->format, 0, 0, 0);
      pixels = (Uint8 *) screen->pixels;
      for (i = 0; i < screen->h; ++i)
	{
	  memset (pixels, black, screen->w * screen->format->BytesPerPixel);
	  pixels += screen->pitch;
	}
      SDL_UnlockSurface (screen);
    }
}

void
RotatePicture (SDL_Surface * screen, SDL_Surface * picture, int rotate,
	       int smooth)
{
  SDL_Surface *rotozoom_picture;
  SDL_Rect dest;
  int framecount, framemax, frameinc;
  float zoomf;

  /* Rotate and display the picture */
  framemax = 4 * 360;
  frameinc = 1;
  for (framecount = 360; framecount < framemax; framecount += frameinc)
    {
      if ((framecount % 360) == 0)
	frameinc++;
      HandleEvent ();
      ClearScreen (screen);
      zoomf = (float) framecount / (float) framemax;
      zoomf = 1.5 * zoomf * zoomf;
      if ((rotozoom_picture =
	   rotozoomSurface (picture, framecount * rotate, zoomf,
			    smooth)) != NULL)
	{
	  dest.x = (screen->w - rotozoom_picture->w) / 2;;
	  dest.y = (screen->h - rotozoom_picture->h) / 2;
	  dest.w = rotozoom_picture->w;
	  dest.h = rotozoom_picture->h;
	  if (SDL_BlitSurface (rotozoom_picture, NULL, screen, &dest) < 0)
	    {
	      fprintf (stderr, "Blit failed: %s\n", SDL_GetError ());
	      break;
	    }
	  SDL_FreeSurface (rotozoom_picture);
	}

      /* Display by flipping screens */
      SDL_UpdateRect (screen, 0, 0, 0, 0);
    }

  if (rotate)
    {
      /* Final display with angle=0 */
      HandleEvent ();
      ClearScreen (screen);
      if ((rotozoom_picture =
	   rotozoomSurface (picture, 0.01, zoomf, smooth)) != NULL)
	{
	  dest.x = (screen->w - rotozoom_picture->w) / 2;;
	  dest.y = (screen->h - rotozoom_picture->h) / 2;
	  dest.w = rotozoom_picture->w;
	  dest.h = rotozoom_picture->h;
	  if (SDL_BlitSurface (rotozoom_picture, NULL, screen, &dest) < 0)
	    {
	      fprintf (stderr, "Blit failed: %s\n", SDL_GetError ());
	      return;
	    }
	  SDL_FreeSurface (rotozoom_picture);
	}

      /* Display by flipping screens */
      SDL_UpdateRect (screen, 0, 0, 0, 0);
    }

  /* Pause for a sec */
  SDL_Delay (1000);
}

void
ZoomPicture (SDL_Surface * screen, SDL_Surface * picture, int smooth)
{
  SDL_Surface *rotozoom_picture;
  SDL_Rect dest;
  int framecount, framemax, frameinc;
  float zoomxf, zoomyf;

  /* Zoom and display the picture */
  framemax = 4 * 360;
  frameinc = 1;
  for (framecount = 360; framecount < framemax; framecount += frameinc)
    {
      if ((framecount % 360) == 0)
	frameinc++;
      HandleEvent ();
      ClearScreen (screen);
      zoomxf = (float) framecount / (float) framemax;
      zoomxf = 1.5 * zoomxf * zoomxf;
      zoomyf = 0.5 + fabs (1.0 * sin ((double) framecount / 80.0));
      if ((rotozoom_picture =
	   zoomSurface (picture, zoomxf, zoomyf, smooth)) != NULL)
	{
	  dest.x = (screen->w - rotozoom_picture->w) / 2;;
	  dest.y = (screen->h - rotozoom_picture->h) / 2;
	  dest.w = rotozoom_picture->w;
	  dest.h = rotozoom_picture->h;
	  if (SDL_BlitSurface (rotozoom_picture, NULL, screen, &dest) < 0)
	    {
	      fprintf (stderr, "Blit failed: %s\n", SDL_GetError ());
	      break;
	    }
	  SDL_FreeSurface (rotozoom_picture);
	}

      /* Display by flipping screens */
      SDL_UpdateRect (screen, 0, 0, 0, 0);
    }

  /* Pause for a sec */
  SDL_Delay (1000);
}

void
Draw (SDL_Surface * screen)
{
  SDL_Surface *picture, *picture_again;
  char *bmpfile;

  /* --------- 8 bit test -------- */

  /* Message */
  fprintf (stderr, "Loading 8bit image\n");

  /* Load the image into a surface */
  bmpfile = "sample8.bmp";
  fprintf (stderr, "Loading picture: %s\n", bmpfile);
  picture = SDL_LoadBMP (bmpfile);
  if (picture == NULL)
    {
      fprintf (stderr, "Couldn't load %s: %s\n", bmpfile, SDL_GetError ());
      return;
    }

  fprintf (stderr, "rotozoom: Rotating and zooming\n");
  RotatePicture (screen, picture, 1, SMOOTHING_OFF);

  fprintf (stderr, "rotozoom: Just zooming (angle=0)\n");
  RotatePicture (screen, picture, 0, SMOOTHING_OFF);

  fprintf (stderr, "zoom: Just zooming\n");
  ZoomPicture (screen, picture, SMOOTHING_OFF);


  fprintf (stderr,
	   "rotozoom: Rotating and zooming, interpolation on but unused\n");
  RotatePicture (screen, picture, 1, SMOOTHING_ON);

  fprintf (stderr,
	   "rotozoom: Just zooming (angle=0), interpolation on but unused\n");
  RotatePicture (screen, picture, 0, SMOOTHING_ON);

  fprintf (stderr, "zoom: Just zooming, interpolation on but unused\n");
  ZoomPicture (screen, picture, SMOOTHING_ON);

  /* Free the picture */
  SDL_FreeSurface (picture);

  /* -------- 24 bit test --------- */

  /* Message */
  fprintf (stderr, "Loading 24bit image\n");
  /* Load the image into a surface */
  bmpfile = "sample24.bmp";
  fprintf (stderr, "Loading picture: %s\n", bmpfile);
  picture = SDL_LoadBMP (bmpfile);
  if (picture == NULL)
    {
      fprintf (stderr, "Couldn't load %s: %s\n", bmpfile, SDL_GetError ());
      return;
    }

  fprintf (stderr, "rotozoom: Rotating and zooming, no interpolation\n");
  RotatePicture (screen, picture, 1, SMOOTHING_OFF);

  fprintf (stderr, "rotozoom: Just zooming (angle=0), no interpolation\n");
  RotatePicture (screen, picture, 0, SMOOTHING_OFF);

  fprintf (stderr, "zoom: Just zooming, no interpolation\n");
  ZoomPicture (screen, picture, SMOOTHING_OFF);


  fprintf (stderr, "rotozoom: Rotating and zooming, with interpolation\n");
  RotatePicture (screen, picture, 1, SMOOTHING_ON);

  fprintf (stderr, "rotozoom: Just zooming (angle=0), with interpolation\n");
  RotatePicture (screen, picture, 0, SMOOTHING_ON);

  fprintf (stderr, "zoom: Just zooming, with interpolation\n");
  ZoomPicture (screen, picture, SMOOTHING_ON);


  /* New source surface is 32bit with defined RGBA ordering */
  /* Much faster to do this once rather than the routine on the fly */
  fprintf (stderr, "Converting 24bit image into 32bit RGBA surface ...\n");
  picture_again =
    SDL_CreateRGBSurface (SDL_SWSURFACE, picture->w, picture->h, 32,
			  0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
  SDL_BlitSurface (picture, NULL, picture_again, NULL);

  /* Message */
  fprintf (stderr, "Rotating and zooming, with interpolation\n");
  RotatePicture (screen, picture_again, 1, SMOOTHING_ON);

  /* Message */
  fprintf (stderr, "Just zooming (angle=0), with interpolation\n");
  RotatePicture (screen, picture_again, 0, SMOOTHING_ON);

  SDL_FreeSurface (picture_again);

  /* New source surface is 32bit with defined ABGR ordering */
  /* Much faster to do this once rather than the routine on the fly */
  fprintf (stderr, "Converting 24bit image into 32bit ABGR surface ...\n");
  picture_again =
    SDL_CreateRGBSurface (SDL_SWSURFACE, picture->w, picture->h, 32,
			  0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
  SDL_BlitSurface (picture, NULL, picture_again, NULL);

  /* Message */
  fprintf (stderr, "Rotating and zooming, with interpolation\n");
  RotatePicture (screen, picture_again, 1, SMOOTHING_ON);

  /* Message */
  fprintf (stderr, "Just zooming (angle=0), with interpolation\n");
  RotatePicture (screen, picture_again, 0, SMOOTHING_ON);

  SDL_FreeSurface (picture_again);

  /* Free the picture */
  SDL_FreeSurface (picture);

  return;
}

#ifdef WIN32
extern char **__argv;
extern int __argc;
int APIENTRY
WinMain (HINSTANCE hInstance,
	 HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else // non WIN32
int
main (int argc, char *argv[])
#endif
{
  SDL_Surface *screen;
  int w, h;
  int desired_bpp;
  Uint32 video_flags;
#ifdef WIN32
  int argc;
  char **argv;

  argv = __argv;
  argc = __argc;
#endif
  /* Title */
  fprintf (stderr, "SDL_rotozoom test\n");

  /* Set default options and check command-line */
  w = 640;
  h = 480;
  desired_bpp = 0;
  video_flags = 0;
  while (argc > 1)
    {
      if (strcmp (argv[1], "-width") == 0)
	{
	  if (argv[2] && ((w = atoi (argv[2])) > 0))
	    {
	      argv += 2;
	      argc -= 2;
	    }
	  else
	    {
	      fprintf (stderr, "The -width option requires an argument\n");
	      exit (1);
	    }
	}
      else if (strcmp (argv[1], "-height") == 0)
	{
	  if (argv[2] && ((h = atoi (argv[2])) > 0))
	    {
	      argv += 2;
	      argc -= 2;
	    }
	  else
	    {
	      fprintf (stderr, "The -height option requires an argument\n");
	      exit (1);
	    }
	}
      else if (strcmp (argv[1], "-bpp") == 0)
	{
	  if (argv[2])
	    {
	      desired_bpp = atoi (argv[2]);
	      argv += 2;
	      argc -= 2;
	    }
	  else
	    {
	      fprintf (stderr, "The -bpp option requires an argument\n");
	      exit (1);
	    }
	}
      else if (strcmp (argv[1], "-warp") == 0)
	{
	  video_flags |= SDL_HWPALETTE;
	  argv += 1;
	  argc -= 1;
	}
      else if (strcmp (argv[1], "-hw") == 0)
	{
	  video_flags |= SDL_HWSURFACE;
	  argv += 1;
	  argc -= 1;
	}
      else if (strcmp (argv[1], "-fullscreen") == 0)
	{
	  video_flags |= SDL_FULLSCREEN;
	  argv += 1;
	  argc -= 1;
	}
      else
	break;
    }

  /* Force double buffering */
  video_flags |= SDL_DOUBLEBUF;

  /* Initialize SDL */
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
      exit (1);
    }
  atexit (SDL_Quit);		/* Clean up on exit */

  /* Initialize the display */
  screen = SDL_SetVideoMode (w, h, desired_bpp, video_flags);
  if (screen == NULL)
    {
      fprintf (stderr, "Couldn't set %dx%dx%d video mode: %s\n",
	       w, h, desired_bpp, SDL_GetError ());
      exit (1);
    }

  /* Show some info */
  printf ("Set %dx%dx%d mode\n",
	  screen->w, screen->h, screen->format->BitsPerPixel);
  printf ("Video surface located in %s memory.\n",
	  (screen->flags & SDL_HWSURFACE) ? "video" : "system");

  /* Check for double buffering */
  if (screen->flags & SDL_DOUBLEBUF)
    {
      printf ("Double-buffering enabled - good!\n");
    }

  /* Set the window manager title bar */
  SDL_WM_SetCaption ("SDL_rotozoom test", "rotozoom");

  /* Do all the drawing work */
  Draw (screen);

  return (0);
}
