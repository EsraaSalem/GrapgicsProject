#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <math.h>
#define cartesianCircle_ID 1
#define polarCircle_ID 2
#define directCartesian_ID 3
#define iterativePolar_ID 4
#define midPoint_ID 5
using namespace std;
double xFirstCaptured=0,xSecondCaptured=0,yFirstCaptured=0,ySecondCaptured=0,counter=0 ,x3=0,y3=0;

bool cartesianCircleflag = false, parametricCircleFlag = false,
    directCartesianFlag = false, iterativePlarFlag = false,
    midPointCircleFlag = false, fasterMid;
void Draw8Points(HDC hdc, double xc, double yc, double x, double y, COLORREF color)
{
    SetPixel(hdc,xc+x , yc+y,color);
    SetPixel(hdc,xc+x , yc-y,color);
    SetPixel(hdc,xc-x , yc+y,color);
    SetPixel(hdc,xc-x , yc-y,color);
    SetPixel(hdc,xc+y , yc+x,color);
    SetPixel(hdc,xc+y , yc-x,color);
    SetPixel(hdc,xc-y , yc+x,color);
    SetPixel(hdc,xc-y , yc-x,color);
}
void cartesianDrawingCircle(HDC hdc, double xc, double yc, double R)
{
    COLORREF color=RGB(150,0,150);
    double x = 0, y = R;
    double slope = abs(x/y);
    Draw8Points(hdc, xc, yc, x, y,color);
    if(slope < 1)
    {
        while(x < y)
        {
            x++;
            double exp = (x*x) + round((y-0.5)*(y-0.5));
            double rr = R*R;
            if(exp >= rr)
            {
                y--;
            }
            Draw8Points(hdc, xc, yc,round(x), round(y),color);
        }
    }

}

void directCartesianAlgorithm(HDC hdc, double xc, double yc, double R)
{
    COLORREF color=RGB(0,150,150);
    double x = 0, y = R;
    Draw8Points(hdc, xc, yc, x, y,color);
    double slope = abs(x/y);
    if(slope <= 1)
    {
        while(x < y)
        {
            x++;
            y = sqrt(R*R - x*x);
            Draw8Points(hdc, xc, yc, x, round(y),color);
        }
    }
    else
    {
        while(y < x)
        {
            y++;
            x = sqrt(R*R - y*y);
            Draw8Points(hdc, xc, yc, round(x),y ,color);
        }
    }
}
void parametricCircle(HDC hdc, double xc, double yc, double R)
{
     COLORREF color=RGB(0,0,150);
     double x = R, y = 0;
     double theta=0,dtheta=1.0/R;
     Draw8Points(hdc, xc, yc, x, y,color);
     while(x>y)
     {

         theta+=dtheta;
         x=R*cos(theta);
         y=R*sin(theta);
         Draw8Points(hdc, xc, yc, round(x), round(y),color);
     }

}
void iterativePolar(HDC hdc, int xc, int yc, double R)
{
     COLORREF color=RGB(50,50,150);
     double x = R, y = 0, dTheta = 1.0/R;
     Draw8Points(hdc, xc, yc, x, y,color);
     double CT = cos(dTheta), ST = sin(dTheta);
     double x1= 0, y1 = 0;
     while(x > y)
     {
         x1 = x*CT - y*ST;
         y = x*ST + y*CT;
         x = x1;
         Draw8Points(hdc, xc, yc, round(x), round(y),color);
     }
}

void midPointAlgorithm(HDC hdc, double xc, double yc, double R)
{
    COLORREF color=RGB(50,70,100);
    double x = 0, y = R, d =1-R;

    Draw8Points(hdc, xc, yc, x, y,color);
    while(x < y)
    {
        x++;
        if(d >= 0)
        {
            d+=(2*(x-y)+3);
            y--;
        }
        else
        {
            d+=(2*x+1);
            //x++;
        }
        Draw8Points(hdc, xc, yc, x, y,color);
    }

}
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (message)                  /* handle the messages */
    {

        case WM_CREATE:
        {
            HMENU hMenubar = CreateMenu();
            HMENU hFile = CreateMenu();
            AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, "Circle Algorithms");
            AppendMenu(hFile, MF_STRING, cartesianCircle_ID, "Cartesian");
            AppendMenu(hFile, MF_STRING, polarCircle_ID, "Polar");
            AppendMenu(hFile, MF_STRING, directCartesian_ID, "DirectCartesian");
            AppendMenu(hFile, MF_STRING, iterativePolar_ID, "iterativePolar");
             AppendMenu(hFile, MF_STRING, midPoint_ID, "midPoint");

            SetMenu(hwnd, hMenubar);
        }
        break;


    case WM_COMMAND:{

        WNDCLASSEX wincl;



        if(LOWORD(wParam) == cartesianCircle_ID)
            {
               cartesianCircleflag = true;
               parametricCircleFlag = false;
               directCartesianFlag = false;
               iterativePlarFlag = false;
               midPointCircleFlag = false;


            }
            else if(LOWORD(wParam) == polarCircle_ID)
            {
                midPointCircleFlag = false;
                cartesianCircleflag = false;
                parametricCircleFlag = true;
                directCartesianFlag = false;
                iterativePlarFlag = false;
            }
            else if(LOWORD(wParam) == directCartesian_ID)
            {
                midPointCircleFlag = false;
                cartesianCircleflag = false;
                parametricCircleFlag = false;
                directCartesianFlag = true;
                iterativePlarFlag = false;
            }
            else if(LOWORD(wParam) == iterativePolar_ID)
            {
                midPointCircleFlag = false;
                cartesianCircleflag = false;
                parametricCircleFlag = false;
                directCartesianFlag = false;
                iterativePlarFlag = true;
            }
            else if(LOWORD(wParam) == midPoint_ID)
            {
                midPointCircleFlag = true;
                cartesianCircleflag = false;
                parametricCircleFlag = false;
                directCartesianFlag = false;
                iterativePlarFlag = false;
            }

		//ReleaseDC(hwnd,hdc);
		break;
















        case WM_LBUTTONDOWN:

        hdc=GetDC(hwnd);
		counter++;

		if(counter==1){
            xFirstCaptured=LOWORD(lParam);
            yFirstCaptured=HIWORD(lParam);
	    }
        if(counter==2){

            xSecondCaptured = LOWORD(lParam);
            ySecondCaptured = HIWORD(lParam);
            counter=0;


            double exp1 = ySecondCaptured-yFirstCaptured;
            exp1*= exp1;

            double exp2 = xSecondCaptured-xFirstCaptured;
            exp2*= exp2;

            double r = sqrt(exp1+exp2);

            if(cartesianCircleflag)
            cartesianDrawingCircle(hdc,xFirstCaptured,yFirstCaptured,r);
            else if(parametricCircleFlag)
            parametricCircle(hdc,xFirstCaptured,yFirstCaptured,r);
            else if(directCartesianFlag)
            directCartesianAlgorithm(hdc,xFirstCaptured,yFirstCaptured,r);
            else if(parametricCircleFlag)
            directCartesianAlgorithm(hdc,xFirstCaptured,yFirstCaptured,r);
            else if(iterativePlarFlag)
            iterativePolar(hdc,xFirstCaptured,yFirstCaptured,r);
            else if(midPointCircleFlag)
            midPointAlgorithm(hdc,xFirstCaptured,yFirstCaptured,r);


		}
		ReleaseDC(hwnd,hdc);
		break;
    }

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
