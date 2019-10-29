#include <stdlib.h>
#include <stdio.h>
#include <iup_plus.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h> 

static int k_any(Ihandle*, int c)
{
	if (c == K_ESC)
		return IUP_CLOSE;
	else
		return IUP_DEFAULT;
}

static int redraw(Ihandle* ih)
{
	Iup::GLCanvas canvas(ih);

	int w, h;
	canvas.GetIntegerInteger("RASTERSIZE", w, h);

	canvas.MakeCurrent();

	glViewport(0, 0, w, h);
	glClearColor(1.0, 1.0, 1.0, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(0.9f, 0.9f);
	glVertex2f(0.9f, -0.9f);
	glVertex2f(-0.9f, -0.9f);
	glVertex2f(-0.9f, 0.9f);
	glEnd();

	canvas.SwapBuffers();

	return IUP_DEFAULT;
}

int exit_callback(void)
{
	return IUP_CLOSE;
}

int on_open_btn_click(Ihandle* item_open)
{
	Iup::Control open_ctrl(item_open);
	Iup::Control dlg = open_ctrl.GetDialogChild("TOOLBAR");



	return IUP_DEFAULT;
}

int on_new_btn_click(Ihandle* item_new)
{

	return IUP_DEFAULT;
}

int on_supports_btn_click(Ihandle* item_supports)
{

	return IUP_DEFAULT;
}

int main(int argc, char** argv)
{
	Iup::Open(argc, argv);
	Iup::GLCanvas::Open();

	//Iup::Item menuItem_Open("Open");
	//Iup::Item menuItem_Exit("Exit");
	//menuItem_Exit.SetCallback("ACTION", (Icallback) exit_callback);

	//Iup::Menu menu_file(
	//	menuItem_Open,
	//	Iup::Separator(),
	//	menuItem_Exit
	//);

	//Iup::Submenu subMenu_file("File", menu_file);
	//Iup::Menu menu_fileMain(subMenu_file);

	Iup::GLCanvas canvas;
	canvas.SetCallback("ACTION", (Icallback)redraw);
	canvas.SetCallback("K_ANY", (Icallback)k_any);
	canvas.SetAttribute("BUFFER", "DOUBLE");
	canvas.SetAttribute("RASTERSIZE", "800x600");

	Iup::Button btn_open("Open");
	btn_open.SetCallback("ACTION", (Icallback)on_new_btn_click);

	Iup::Hbox canvasContainer(Iup::Fill(),
		canvas,
		Iup::Fill()
	);

	Iup::Dialog dlg(canvasContainer);
	dlg.SetAttribute("TITLE", "IUPTemplate");
	//dlg.SetAttributeHandle("MENU", menu_fileMain);

	dlg.Show();

	Iup::MainLoop();

	Iup::Close();

	return 0;
}