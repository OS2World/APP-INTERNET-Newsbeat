#define INCL_DOSFILEMGR
#define INCL_WIN
#define INCL_PM
#define INCL_DOSPROCESS
#define INCL_GPI
#define INCL_DOS
#define INCL_DOSRESOURCES
#define INCL_DOSSESMGR
#define INCL_GPILCIDS
#define INCL_GPIPRIMITIVES
#define INCL_WINDIALOGS
#define INCL_WINSYS
#include <string.h>
#include <stdio.h>
#include <os2.h>
#include <process.h>
#include "newsbeat.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <math.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#define DEC(c)  (((c) - ' ') & 077)
#define ENC(c) ((c) ? ((c) & 077) + ' ': '`')
#define HWNDERR(hwnd) \
        (ERRORIDERROR(WinGetLastError(WinQueryAnchorBlock(hwnd))))
typedef struct _NBPAGE
{
    PFNWP    pfnwpDlg;
    HWND     hwnd;
    PSZ      szStatusLineText;
    PSZ      szTabText;
    ULONG    idDlg;
    ULONG    idFocus;
    BOOL     fParent;
    USHORT   usTabType;
} NBPAGE, *PNBPAGE;
typedef struct {
        char Groupname[120];
        int  Count;
        int  ListRead[5000];
        int  Small;
        } ReadArt;
ReadArt ListRead[2000];
typedef struct {
        char Mid[MAXLINE];
        char Subject[MAXLINE];
        char From[MAXLINE];
        char Line[MAXLINE];
       int re;
       } Headers;
static Headers Head[25000];
MRESULT EXPENTRY AKillFile(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY VHeader(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY App_Func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY Client_Func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY Setting_Func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY Subscribe_Func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY Search_Func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY Login_Func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY AUser_Func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY Edit_Func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY ab_func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY reg_func(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY Register(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY SNotebook(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY MSearch(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY editor_func(HWND, ULONG, MPARAM, MPARAM);
char Browser[256]="explore.exe";
char Params[100];
VOID Changed(VOID);
VOID APIENTRY UUDecode(FILE *,FILE *);
VOID APIENTRY UUDecodePrep(void *);
VOID APIENTRY LGroup(void *);
VOID APIENTRY GetGroup(void *);
VOID APIENTRY SSort(void);
VOID APIENTRY QSort(void);
VOID APIENTRY StartBr(void *);
VOID APIENTRY GetHeaders(void *);
VOID APIENTRY GetArticle(void *);
VOID APIENTRY Subscribe(void *);
VOID APIENTRY Connect(void *);
VOID APIENTRY Post(void *);
VOID APIENTRY Mail(void *);
void Drop(char *, char *, int);
void wfwrite(FILE *outfile, FILE *rf);
void outdec(char * p, FILE *f, int);
static void ShellSort(int LowH, int MaxH);
int subjsplit(int x);
void subjsort(int lo, int x);
void outdecen(char *p, FILE *f);
void encode(FILE *in, FILE *out);
BOOL Registered=FALSE;
static BOOL SetUpPage(HWND hwndNoteBook,PNBPAGE pNbPage ,int IArrayIndex);
static BOOL TurnToFirstPage(HWND);
static BOOL InsertPage(HWND);
static HMODULE ModuleHandle;
static BOOL ControlMsg(HWND, USHORT, USHORT, MPARAM);
static void SetNBPage(HWND, PPAGESELECTNOTIFY);
static HWND LoadAndAssociate(HWND, PNBPAGE, PPAGESELECTNOTIFY);
BOOL InitializeNoteBook(HWND);
static BOOL SetTabDimensions(HWND hwndNoteBook);
static INT  GetStringSize(HPS hps, HWND hwndNoteBook, PSZ szString);
static BOOL  Encrypt(char s1[MAXLINE], ULONG, ULONG);
char * index(char * sp, char c);
static HWND hwndStatTxt;
static HWND hwndStatTxtUU;
struct sockaddr_in bba;
struct sockaddr_in bba1;
struct hostent *hp;
struct hostent *hp1;
static int TGroupS;
int server_conn(void *);
int UUL,MaxLines=14990;
char hostname[MAXLINE],email[MAXLINE],realn[MAXLINE],organ[MAXLINE],mailserver[MAXLINE],lastn[MAXLINE];
BOOL LInfo=FALSE;
ULONG ipt=0;
char UUArticle[10];
IPT lOffset=0;
BOOL SInsert=FALSE;
BOOL Processed=FALSE;
BOOL NotThere=FALSE;
BOOL DoneSub=TRUE;
BOOL DoneL=TRUE;
BOOL MailTF=FALSE;
BOOL PostTF=FALSE;
BOOL NoBegin=FALSE;
BOOL Abort=FALSE;
BOOL HideArt=FALSE;
BOOL Subed=TRUE;
BOOL LBUTTONS=TRUE;
BOOL SKill=FALSE;
BOOL MsgUU=TRUE;
BOOL ZOOMED=FALSE;
BOOL LoginFailed=FALSE;
BOOL ArtKil=TRUE;
BOOL LOADED=FALSE;
BOOL Change=FALSE;
BOOL New=TRUE;
BOOL SubConn=FALSE;
BOOL EOpen=FALSE;
BOOL BUSY=FALSE;
BOOL Connected=FALSE;
BOOL Decoding=FALSE;
BOOL Paused=FALSE;
HAB     hab;
static ULONG Large;
HPOINTER hptr;
HBITMAP hbm[21];
APIRET rc;
static HWND hwndBubble;
char EMailTo[MAXLINE], PSubject[MAXLINE], PDistribution[MAXLINE],PFrom[MAXLINE], Vers[100]="V0.99b35 - Final";
time_t RndID,ExpDate;
UCHAR sem[16];
int Tries, KItem2, KCount2;
FILE *KFile2;
char KString2[MAXLINE];
int SGItem;
int SubGroup=0;
char SGroup[MAXLINE];
FILE *sarf, *sawf;
char satstring[MAXLINE];
int APPEND=1;int sap;
int ZState=0,ReC;
HEV hand;
LBOXINFO lbi;
static ULONG TGroup;
char tstring[MAXLINE],*tmp,tstring1[MAXLINE];
static HWND hwndPBUUPause;
static HWND hwndSDlg;
static HWND hwndUUText;
static HWND hwndPBZoomIn;
static HWND hwndPBZoomOut;
static HWND hwndLBKill;
static HWND hwndMLETitle;
static HWND hwndMLE;
static HWND hwndLBTitle;
static HWND hwndLB;
static HWND hwndPopAGroups;
static HWND hwndLB2Title;
static HWND hwndLB2;
static HWND hwndZArticle;
static HWND hwndZUUList;
static HWND hwndZMsg;
static HWND hwndZAll;
static HWND hwndZGroups;
static HWND hwndZKill;
static HWND hwndLBALL;
static HWND hwndLBBlank;
static HWND hwndLBUUQueue;
static HWND hwndPBNewL;
static HWND hwndPBWrite;
static HWND hwndPBPrint;
static HWND hwndPBUUQueue;
static HWND hwndPBCopy;
static HWND hwndPBSave;
static HWND hwndPBQuit;
static HWND hwndPBHelp;
static HWND hwndPBMarkRead;
static HWND hwndPBMarkUnread;
static HWND hwndPBMarkAllRead;
static HWND hwndPBMarkAllUnread;
static HWND hwndPBUUDelete;
static HWND hwndPBUUAbort;
static HWND hwndUUProgress;
static HWND hwndPBUUStop;
static HWND hwndPBExplore;
static HWND hwndPopArticles;
static HWND hwndPopSGroups;
static HWND hwndPopUUQ;
static HWND hwndPopKill;
static HWND hwndNoteBook;
static ULONG hChar=26;
static ULONG hBut=38;
static ULONG offset=40;
static ULONG statusbar=20;
static UCHAR flag=0;
HWND    hFrame, hClient;
char    number[10];
char    PassW[30];
FILE    *stream;
FILE    *stream2,*stream2s;
FILE    *infile;
int     filetest,LowArt,HighArt, SortOrd=0,FastLoad,UUDownBeep;
char DownloadDir[MAXLINE];
static ULONG   item,item1;
char RegName[MAXLINE];
ULONG   Key, Code;
TID     tid;
char    groupname[120],groupd[150];
char    titlstr[140];
int     itmp,itmpa;
int     i,a,b,j,qc=0;
typedef struct
{       char UName[30];
        char Pass[30];
        char Dir[30];
        } LName;
static LName Users[50];
static LName CurrentU;
int UserCount=0;
typedef struct
{
        char MID[MAXLINE];
        char Group[256];
} QueueArt;
QueueArt UUNames[3000];
int try=0;
typedef struct
{
        char Group[120];
        int  Moder[3];
} GroupInfo;
static GroupInfo NGroups[50000];
typedef struct {
          char Ext[15];
          char Program[MAXLINE];
          } ViewerStr;
static ViewerStr Viewers[50];
Headers temphead[1];
PSZ *GroupP[50000];
static int iPagesLoaded=0;
static int iAdded=0;
FILE *rf, *wf, *outfile, *rf1, *wf1;
CHAR szMleBuf[512];
int ch,cha,chb;
ULONG cbCopy;
char Title[50];
int s=0, listdone,gc,headdone,listdone1,s1=0;
PCHAR gct;
char *IGroup;
char article[15], articlei[180], tmpstr4[180];
static RECTL   rectl;
static int tmpc,item7,item8;
static int s7,filetest7,s8,ki8,errch8,nmsgs8,Hgh8,Lw8;
static char tstring7[MAXLINE],tstring8[MAXLINE], tmpstring8[200];
static FILE *stream7, *rf8, *wf8;
static char mtmps[100];
static char tmpspc[256]=" \0";
static int mki=0,mki2,mki3,itc,mki4;
FNWP wpPage1,wpPage2, wpPage3,wpPage4;
NBPAGE nbpage[]=
{
        {wpPage1,NULLHANDLE, "Network Settings", "~Network", ID_NBPAGE1, SET_NEWSF, FALSE, BKA_MAJOR},
        {wpPage2,NULLHANDLE, "User Settings", "~User", ID_NBPAGE2, SET_NEWSF, FALSE, BKA_MAJOR},
        {wpPage3,NULLHANDLE, "User Preferences", "~Preferences", ID_NBPAGE3, SET_NEWSF, FALSE, BKA_MAJOR},
        {wpPage4,NULLHANDLE, "Multimedia Viewers", "~Viewers", ID_NBPAGE4, SET_NEWS, FALSE, BKA_MAJOR}
        };
#define PAGE_COUNT (sizeof( nbpage ) / sizeof( NBPAGE ))
main()
{
HMQ     hmq;
QMSG    qmsg;
ULONG   flFlags;
char    szClass[]="NewsBeat v0.99b35 - Final Beta ";

flFlags=FCF_MENU|FCF_TITLEBAR|FCF_SYSMENU|FCF_SIZEBORDER|FCF_MINMAX|FCF_TASKLIST
        |FCF_SHELLPOSITION|FCF_ICON|FCF_ACCELTABLE|FCF_NOBYTEALIGN;
hab=WinInitialize(0);
hmq=WinCreateMsgQueue(hab, 0);
WinLoadString(hab, 0L, ID_TITLE, sizeof(szClass), (PSZ)szClass);
if(!(WinRegisterClass(hab, (PSZ)szClass, (PFNWP)Client_Func, CS_SIZEREDRAW, 0)))
return 0;
hFrame=WinCreateStdWindow(HWND_DESKTOP, WS_VISIBLE, &flFlags,(PSZ)szClass,
        (PSZ)szClass,0,(HMODULE) NULL,ID_WINDOW, &hClient);
while(WinGetMsg(hab, &qmsg, 0,0,0))
WinDispatchMsg(hab, &qmsg);


WinDestroyMsgQueue(hmq);
WinTerminate(hab);
return 0;
}

MRESULT EXPENTRY Client_Func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{

static HWND hwndPBSett;
static POINTL bcoords,scoords;
ULONG   LGRPS;
COLOR   color;
 HPS     hps;
HFILE   fh;
ULONG   action;
ULONG   num_bytes;
CHAR    buf[513];
INT     MsgProcess = TRUE;
HWND    fdlg;
POINTL coords;
FILEDLG fd;
char    fdTitle[]="Save Message";

static HWND hwndZArticle;
static HWND hwndZUUList;
static HWND hwndZGroups;


switch(msg) {
        case WM_CREATE:
        hwndPopKill=WinLoadMenu(hwnd,0,POP_KILL);
        hwndPopAGroups=WinLoadMenu(hwnd,0,POP_AGROUPS);
        hwndPopSGroups=WinLoadMenu(hwnd,0,POP_SGROUPS);
        hwndPopUUQ=WinLoadMenu(hwnd,0,POP_UUQ);
        hwndPopArticles=WinLoadMenu(hwnd, 0,POP_ARTICLES);
        WinStartTimer(hab,hwnd,10090,2000);
        hwndBubble=WinCreateWindow(hwnd, WC_STATIC,(PSZ)"",
                SS_TEXT|DT_CENTER|DT_VCENTER,0L,0L,0L,0L,hwnd,HWND_TOP,BUBBLEHELP,NULL,NULL);
        hwndZAll=WinCreateWindow(       hwnd,
                                        WC_BUTTON,
                                        "All Newsgroups",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_ZALL,
                                        NULL,NULL);
        hwndZKill=WinCreateWindow(      hwnd,
                                        WC_BUTTON,
                                        "Kill File",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_ZKILL,
                                        NULL,NULL);
        hwndZMsg=WinCreateWindow(       hwnd,
                                        WC_BUTTON,
                                        "Current Article",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_ZMSG,
                                        NULL,NULL);
        hwndZGroups=WinCreateWindow(    hwnd,
                                        WC_BUTTON,
                                        "Subscribed Groups",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_ZGROUPS,
                                        NULL,NULL);
        hwndZUUList=WinCreateWindow(   hwnd,
                                        WC_BUTTON,
                                        "UUDecode List",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_ZUULIST,
                                        NULL,NULL);
        hwndZArticle=WinCreateWindow(   hwnd,
                                        WC_BUTTON,
                                        "Article List",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_ZARTICLE,
                                        NULL,NULL);
        hwndMLETitle=WinCreateWindow(   hwnd,
                                        WC_BUTTON,
                                        "Current Message",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_MLETITLE,
                                        NULL, NULL);
        hwndMLE=WinCreateWindow(        hwnd,
                                        WC_MLE,
                                        NULL,
                                        MLS_BORDER|MLS_HSCROLL|MLS_VSCROLL|MLS_IGNORETAB|MLS_READONLY|MLS_WORDWRAP,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_MLEWINDOW,
                                        NULL, NULL);
        hwndLBTitle=WinCreateWindow(    hwnd,
                                        WC_BUTTON,
                                        "Article List",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_LB1TITLE,
                                        NULL, NULL);
        hwndUUText=WinCreateWindow(     hwnd,
                                        WC_STATIC,
                                        NULL,
                                        SS_TEXT,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_UUTXT,
                                        NULL,NULL);
        hwndUUProgress=WinCreateWindow( hwnd,
                                        WC_STATIC,
                                        "#180",
                                        SS_BITMAP|DT_CENTER|DT_VCENTER,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_UUPROG,
                                        NULL,NULL);
        hwndStatTxtUU=WinCreateWindow(  hwnd,
                                        WC_STATIC,
                                        NULL,
                                        SS_TEXT,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_STATTXTUU,
                                        NULL,NULL);
        hwndStatTxt=WinCreateWindow(    hwnd,
                                        WC_STATIC,
                                        NULL,
                                        SS_TEXT,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_STATTXT,
                                        NULL,NULL);
        hwndLBKill=WinCreateWindow(     hwnd,
                                        WC_LISTBOX,
                                        NULL,
                                        LS_HORZSCROLL,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_LBKILL,
                                        NULL,NULL);
        hwndLB=WinCreateWindow(         hwnd,
                                        WC_LISTBOX,
                                        NULL,
                                        LS_HORZSCROLL|LS_EXTENDEDSEL|LS_MULTIPLESEL,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_LB1WINDOW,
                                        NULL, NULL);
        hwndLB2Title=WinCreateWindow(   hwnd,
                                        WC_BUTTON,
                                        "Subscribed Newsgroups",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_LB2TITLE,
                                        NULL, NULL);
        hwndLBALL=WinCreateWindow(      hwnd,
                                        WC_LISTBOX,
                                        NULL,
                                        LS_HORZSCROLL,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_LBALL,
                                        NULL, NULL);
        hwndLBBlank=WinCreateWindow(    hwnd,
                                        WC_LISTBOX,
                                        NULL,
                                        LS_HORZSCROLL,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_LBBLANK,
                                        NULL, NULL);
        hwndLB2=WinCreateWindow(        hwnd,
                                       WC_LISTBOX,
                                        NULL,
                                        LS_HORZSCROLL,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_LB2WINDOW,
                                        NULL, NULL);
        hwndPBWrite=WinCreateWindow(    hwnd,
                                        WC_BUTTON,
                                        "#101",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBWRITE,
                                        NULL, NULL);
        hwndPBMarkRead=WinCreateWindow( hwnd,
                                        WC_BUTTON,
                                        "#127",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBMAR,
                                        NULL, NULL);
        hwndPBZoomIn=WinCreateWindow(   hwnd,
                                        WC_BUTTON,
                                        "#133",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_ZOOMIN,
                                        NULL,NULL);
        hwndPBZoomOut=WinCreateWindow(  hwnd,
                                        WC_BUTTON,
                                        "#134",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_ZOOMOUT,
                                        NULL,NULL);
        hwndPBMarkUnread=WinCreateWindow(    hwnd,
                                        WC_BUTTON,
                                        "#128",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBMAUR,
                                        NULL, NULL);
        hwndPBMarkAllRead=WinCreateWindow(    hwnd,
                                        WC_BUTTON,
                                        "#129",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBMAAR,
                                        NULL, NULL);
        hwndPBMarkAllUnread=WinCreateWindow(    hwnd,
                                        WC_BUTTON,
                                        "#130",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBMAAUR,
                                        NULL, NULL);
        hwndPBHelp=WinCreateWindow(      hwnd,
                                        WC_BUTTON,
                                        "#109",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBHELP,
                                        NULL, NULL);
        hwndPBQuit=WinCreateWindow(      hwnd,
                                        WC_BUTTON,
                                        "#110",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBQUIT,
                                        NULL, NULL);
        hwndPBNewL =WinCreateWindow(    hwnd,
                                        WC_BUTTON,
                                        "#108",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBNEWL,
                                        NULL,NULL);
        hwndPBPrint=WinCreateWindow(    hwnd,
                                        WC_BUTTON,
                                        "#104",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBPRINT,
                                        NULL, NULL);
        hwndPBUUQueue=WinCreateWindow(  hwnd,
                                        WC_BUTTON,
                                        "#102",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBUUQUEUE,
                                        NULL,NULL);
        hwndPBSave=WinCreateWindow(     hwnd,
                                        WC_BUTTON,
                                        "#105",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBSAVE,
                                        NULL,NULL);
        hwndPBExplore=WinCreateWindow(  hwnd,WC_BUTTON, "#204", BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,hwnd, HWND_TOP,ID_PBEXPLORE,NULL,NULL);
        hwndPBCopy=WinCreateWindow(     hwnd,
                                        WC_BUTTON,
                                        "#103",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBCOPY,
                                        NULL,NULL);
        hwndPBSett=WinCreateWindow(     hwnd,
                                        WC_BUTTON,
                                        "#106",
                                        BS_PUSHBUTTON|BS_BITMAP|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBSETT,
                                        NULL,NULL);
        hwndPBUUDelete=WinCreateWindow( hwnd,
                                        WC_BUTTON,
                                        "Remove File",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBUUDEL,
                                        NULL,NULL);
        hwndPBUUPause=WinCreateWindow(  hwnd,
                                        WC_BUTTON,
                                        "Pause",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBUUPAUSE,
                                        NULL,NULL);
        hwndPBUUAbort=WinCreateWindow(  hwnd,
                                        WC_BUTTON,
                                        "Abort All",
                                        BS_PUSHBUTTON|BS_NOPOINTERFOCUS,
                                        0L, 0L, 0L, 0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_PBUUABORT,
                                        NULL,NULL);
        hwndLBUUQueue=WinCreateWindow(  hwnd,
                                        WC_LISTBOX,
                                        NULL,
                                        LS_HORZSCROLL,
                                        0L,0L,0L,0L,
                                        hwnd,
                                        HWND_TOP,
                                        ID_LBUUQ,
                                        NULL,NULL);
        WinSetPresParam(hwndLBALL, PP_FONTNAMESIZE, 14, "11.System VIO");
        WinSetPresParam(hwndLB, PP_FONTNAMESIZE, 14, "11.System VIO");
        WinSetPresParam(hwndLB2, PP_FONTNAMESIZE,14, "11.System VIO");
        WinSetPresParam(hwndLBUUQueue, PP_FONTNAMESIZE, 14,"11.System VIO");
        WinSetPresParam(hwndBubble, PP_FONTNAMESIZE, 14, "12.System VIO");
        WinSetWindowText(hwndUUText, "Article ");
        hps=WinBeginPaint(hwnd, NULLHANDLE, NULL);
        a=180;
        for(i=0;i<=20;i++)
        {
           hbm[i]=GpiLoadBitmap(hps, 0, a,64L, 64L);
           a++;
        }
        WinEndPaint(hps);
        WinSendMsg(hwndUUProgress,SM_SETHANDLE ,(MPARAM)hbm[0],0);
        a=0;i=0;
        stream2=fopen("user.lst", "r");
        if (stream2)
        {  UserCount=0;
           while(filetest!=EOF)
           {
              filetest=fscanf(stream2, "%s",Users[UserCount].UName);
              filetest=fscanf(stream2, "%s",Users[UserCount].Pass);
              filetest=fscanf(stream2, "%s",Users[UserCount].Dir);
              UserCount++;
           }
           fclose(stream2);
           WinDlgBox(HWND_DESKTOP,hwnd,Login_Func,0,LOGIN,0);
           if(LoginFailed)
           {
              WinMessageBox(HWND_DESKTOP, hwnd, "Incorrect Password or Username.","Login Failed", 0, MB_OK|MB_ERROR);
              WinPostMsg(hwnd, WM_CLOSE, 0,0);
           }
           else
           {
              rc=DosSetCurrentDir(CurrentU.Dir);
              if(rc!=0)
              {
                 WinMessageBox(HWND_DESKTOP, hwnd, "Directory does not exist.","Disk Error", 0, MB_OK|MB_ERROR);
                 WinPostMsg(hwnd, WM_CLOSE, 0,0);
              }
          }
        }
        stream2=fopen("news.rc", "r");
        if (!stream2) WinDlgBox(HWND_DESKTOP, hwnd, SNotebook, 0, SETTNOTE, 0);
        else
        {
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring,"%s",hostname);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring,"%s",mailserver);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring,"%s",email);
           fgets(realn, MAXLINE, stream2);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring,"%s",organ);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring,"%d",&TGroup);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring, "%d", &SortOrd);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring, "%d", &FastLoad);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring, "%s", DownloadDir);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring, "%d", &UUDownBeep);
           fgets(RegName, MAXLINE, stream2);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring, "%d", &Key);
           fgets(tstring, MAXLINE, stream2);
           sscanf(tstring, "%d", &Code);
           fclose(stream2);
        }

        i=strcspn(RegName, "\n");
        RegName[i]='\0';
        if (strlen(RegName)>0)
           Registered=Encrypt(RegName, Key, Code);
        i=strcspn(realn, "\n");
        realn[i]='\0';
        stream2=fopen("newsbeat.kil", "r");
        if (stream2)
        {
           fgets(tstring, MAXLINE, stream2);
           while(strncmp(tstring, ".",1)!=0)
           {
              i=strcspn(tstring, "\n");
              tstring[i]='\0';
              WinSendMsg(hwndLBKill, LM_INSERTITEM, MPFROMSHORT(0),tstring);
              fgets(tstring, MAXLINE, stream2);
           }
           fclose(stream2);
        }
        stream2=fopen("newsbeat.vwr", "r");
        if (stream2)
        {
           filetest=fscanf(stream2, "%s",Browser);
           fgets(tstring, MAXLINE, stream2);
           i=strcspn(tstring, "\n");
           tstring[i]='\0';
           strcpy(Params, tstring);
           fclose(stream2);
        }

        ExpDate=time(NULL);
        if((854822746<=ExpDate) && (!Registered))
        {
           WinMessageBox(HWND_DESKTOP, hwnd, "This program has expired, please register.","Program Has Expired.", 0, MB_OK|MB_ERROR);
           WinPostMsg(hwnd, WM_CLOSE, 0,0);
        }
        else
           _beginthread(Connect,NULL ,32768, (void *)hwnd);
        break;
//**********************************************My Messages********************
        case WM_LOADGPS:
                 WinSetWindowText(hwndStatTxt, "Loading newsgroups...");
                 DoneL=TRUE;
                 _beginthread(LGroup,NULL ,32768, (void *)hwnd);
        break;
        case WM_STATMSG:{
                PCHAR Message;
                Message=(PCHAR)parm1;
                WinSetWindowText(hwndStatTxt,Message);
        break;}
        case WM_INSMLE:{
                WinSetWindowText(hwndStatTxt, parm1);
                WinSendMsg(hwndMLE, MLM_SETIMPORTEXPORT, parm1, parm2);
                WinSendMsg(hwndMLE, MLM_IMPORT, (MPARAM) &ipt, MPFROMLONG(strlen(parm1)));
                break;}
        case WM_BARUPDATEB:{
                int Percent;
                Percent=(int)parm1;
                if (Percent>=0)
                {
                   hps = WinGetPS(hwnd);
                   WinQueryWindowRect (hwnd, &rectl);
                   scoords.x=rectl.xRight/2+10;
                   scoords.y=11;
                   GpiSetCurrentPosition(hps, &scoords);
                   GpiSetColor(hps,CLR_BLUE);
                   itmp=(rectl.xRight-10)-(rectl.xRight/2+10);
                   bcoords.x=(rectl.xRight/2+10)+((Percent*itmp)/100);
                   bcoords.y=18;
                   GpiBox(hps,DRO_FILL,&bcoords,1,1);
                   WinEndPaint(hps);
                }
                else
                {
                   hps=WinGetPS(hwnd);
                   WinQueryWindowRect (hwnd, &rectl);
                   scoords.x=rectl.xRight/2+10;
                   scoords.y=11;
                   GpiSetCurrentPosition(hps, &scoords);
                   GpiSetColor(hps,CLR_BLACK);
                   bcoords.x=rectl.xRight-10;
                   bcoords.y=18;
                   GpiBox(hps,DRO_FILL,&bcoords,1,1);
                   WinEndPaint (hps);
                }
        break;}
        case WM_BARUPDATE:{
                int Percent;
                Percent=(int)parm1;
                if (Percent>=0)
                {
                   hps = WinGetPS(hwnd);
                   WinQueryWindowRect (hwnd, &rectl);
                   scoords.x=rectl.xRight/2+10;
                   scoords.y=2;
                   GpiSetCurrentPosition(hps, &scoords);
                   GpiSetColor(hps,CLR_RED);
                   itmp=(rectl.xRight-10)-(rectl.xRight/2+10);
                   bcoords.x=(rectl.xRight/2+10)+((Percent*itmp)/100);
                   bcoords.y=9;
                   GpiBox(hps,DRO_FILL,&bcoords,1,1);
                   WinEndPaint(hps);
                }
               else
                {
                   hps=WinGetPS(hwnd);
                   WinQueryWindowRect (hwnd, &rectl);
                   scoords.x=rectl.xRight/2+10;
                   scoords.y=2;
                   GpiSetCurrentPosition(hps, &scoords);
                   GpiSetColor(hps,CLR_BLACK);
                   bcoords.x=rectl.xRight-10;
                   bcoords.y=9;
                   GpiBox(hps,DRO_FILL,&bcoords,1,1);
                   WinEndPaint (hps);
                }

        break;}
        case WM_PUTHEAD:{
            PCHAR GN;
            GN=(PCHAR)parm1;
            WinSendMsg(hwndLB, LM_INSERTITEM, MPFROMSHORT(0),GN);
        break;}
//*****************************************************************************
        case WM_TIMER:
        break;
        case WM_CONTROL:
                if(SHORT2FROMMP(parm1)==LN_ENTER)
                {
                   if(SHORT1FROMMP(parm1)==ID_LB1WINDOW)
                   {
                      WinSetWindowText(hwndStatTxt, "Loading article.");
                      item=WinQueryLboxSelectedItem(hwndLB);
                      WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                      item=WinQueryLboxSelectedItem(hwndLB);
                      WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                      articlei[0]='*';
                      WinSendMsg(hwndLB, LM_SETITEMTEXT,  MPFROM2SHORT(item,180), MPFROMP(articlei));
//                      WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(item),(MPARAM)FALSE);
                      Drop(articlei, articlei, 1);
                      sscanf(articlei, "%d", &mki2);
                      mki=0;
                      while(NULL==strstr(ListRead[mki].Groupname,groupname))
                      {
                         mki++;
                      }
                      NotThere=FALSE;
                      for(mki3=0;mki3<ListRead[mki].Count;mki3++)
                      {
                          if(mki2==ListRead[mki].ListRead[mki3])
                          {
                              NotThere=TRUE;
                              break;
                          }
                      }
                      if(!NotThere)
                      {
                         ListRead[mki].ListRead[ListRead[mki].Count]=mki2;
                         ListRead[mki].Count++;
                         mki4=mki;
                         mki=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(groupname));
                         WinSendMsg(hwndLB2, LM_QUERYITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                         sscanf(tmpstr4, "%d", &mki2);
                         mki2--;
                         if(mki2<=0)
                         {
                             Large=0;
                             for(mki3=0;mki3<ListRead[mki4].Count;mki3++)
                             {
                                 if(Large<ListRead[mki4].ListRead[mki3])
                                     Large=ListRead[mki4].ListRead[mki3];
                             }
                             ListRead[mki4].ListRead[ListRead[mki4].Count]=abs(ListRead[mki4].ListRead[0]);
                             ListRead[mki4].ListRead[0]=Large*(-1);
                             ListRead[mki4].Count++;
                             mki2=0;
                         }
                         sprintf(tmpstr4, "%d",mki2);
                         while(strlen(tmpstr4)<5)
                            strcat(tmpstr4, " ");
                         strcat(tmpstr4, groupname);
                         strcat(tmpstr4, " ");
                         WinSendMsg(hwndLB2, LM_SETITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                      }
                      i=strcspn(articlei, " ");
                      for(a=0;a<i;a++)
                         article[a]=articlei[a];
                      article[i]='\0';
                      _beginthread(GetArticle,NULL, 32768, (void *)hwnd);
                      WinSetWindowText(hwndStatTxt, "Retrieving Article");
                      Changed();
                   }
                   if(SHORT1FROMMP(parm1)==ID_LBALL)
                   {
                      item=WinQueryLboxSelectedItem(hwndLBALL);
                      WinSendMsg(hwndLBALL, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(groupname));
                      _beginthread(Subscribe, NULL, 32768, (void *)hwnd);
                   }//if lball
                   if(SHORT1FROMMP(parm1)==ID_LB2WINDOW)
                   {
                      item=WinQueryLboxSelectedItem(hwndLB2);
                      WinSendMsg(hwndLB2, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(groupname));
                      Drop(groupname,groupname,5);
                      WinSetWindowText(hwndStatTxt, groupname);
                      mki=strcspn(groupname, " ");
                      groupname[mki]='\0';
                      WinSendMsg(hwndLB, LM_DELETEALL,NULL,NULL);
                      _beginthread(GetHeaders, NULL, 32768, (void *)hwnd);
                  }//lb2
                }
        case WM_BUTTON2DOWN:
                color=CLR_BLACK;
                WinSetPresParam(hwndBubble, PP_BACKGROUNDCOLORINDEX, sizeof(color), &color);
                color=CLR_YELLOW;
                WinSetPresParam(hwndBubble, PP_FOREGROUNDCOLORINDEX, sizeof(color), &color);
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                //Settings button
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBSETT), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBSETT), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBSett, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "View/Change Settings");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut*12+40,rectl.yTop-hBut-24, 185, 22,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                //Copy Button
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBCOPY), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBCOPY), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBCopy, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "Copy to clipboard");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut*5,rectl.yTop-hBut-24, 150, 22,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);

                 }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBSAVE), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBSAVE), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBSave, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "Save Message");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut*4,rectl.yTop-hBut-24, 130, 22,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);

                 }
                 coords.x = SHORT1FROMMP(parm1);
                 coords.y = SHORT2FROMMP(parm1);
                 WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBEXPLORE), &coords, 1);
                 WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBEXPLORE), &rectl);
                 if (WinPtInRect(hab, &rectl, &coords))
                 {
                         WinMapWindowPoints(hwndPBExplore, HWND_DESKTOP,&coords,1);
                         WinQueryWindowRect(hwnd, &rectl);
                         WinSetWindowText(hwndBubble, "Go To URL");
                         WinSetWindowPos(hwndBubble, HWND_TOP, hBut*11-5,rectl.yTop-hBut-24, 130, 22,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);

                 }
                 coords.x = SHORT1FROMMP(parm1);
                 coords.y = SHORT2FROMMP(parm1);
                 WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBMAR), &coords, 1);
                 WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBMAR), &rectl);
                 if (WinPtInRect(hab, &rectl, &coords))
                 {
                         WinMapWindowPoints(hwndPBSave, HWND_DESKTOP,&coords,1);
                         WinQueryWindowRect(hwnd, &rectl);
                         WinSetWindowText(hwndBubble, "Mark Read");
                         WinSetWindowPos(hwndBubble, HWND_TOP, hBut*7-10,rectl.yTop-hBut-24, 100, 22,
                         SWP_SIZE|SWP_MOVE|SWP_SHOW);

                 }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBMAUR), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBMAUR), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBSave, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "Mark Unread");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut*8-10,rectl.yTop-hBut-24, 110, 22,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBMAAR), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBMAAR), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBSave, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "Mark All Read");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut*9-10,rectl.yTop-hBut-24, 130, 22,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBMAAUR), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBMAAUR), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBSave, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "Mark All Unread");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut*10-10,rectl.yTop-hBut-24, 130, 22,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBUUQUEUE), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBUUQUEUE), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBUUQueue, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "Add to UUDecode Queue");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut*3,rectl.yTop-hBut-24, 200, 22,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);

                 }
                 coords.x = SHORT1FROMMP(parm1);
                 coords.y = SHORT2FROMMP(parm1);
                 WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBNEWL), &coords, 1);
                 WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBNEWL), &rectl);
                 if (WinPtInRect(hab, &rectl, &coords))
                 {
                         WinMapWindowPoints(hwndPBNewL, HWND_DESKTOP,&coords,1);
                         WinQueryWindowRect(hwnd, &rectl);
                         WinSetWindowText(hwndBubble, "New Message");
                         WinSetWindowPos(hwndBubble, HWND_TOP, 0,rectl.yTop-hBut-24, 130, 22,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);

                }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBPRINT), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBPRINT), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBPrint, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "Print Message");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut*2,rectl.yTop-hBut-24, 130, 22,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);

                }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBHELP), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBHELP), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                   WinMapWindowPoints(hwndPBPrint, HWND_DESKTOP,&coords,1);
                   WinQueryWindowRect(hwnd, &rectl);
                   WinSetWindowText(hwndBubble, "Help");
                   WinSetWindowPos(hwndBubble, HWND_TOP, rectl.xLeft+hBut*15,rectl.yTop-hBut-24,70,22,
                           SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBQUIT), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBQUIT), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                   WinMapWindowPoints(hwndPBPrint, HWND_DESKTOP,&coords,1);
                   WinQueryWindowRect(hwnd, &rectl);
                   WinSetWindowText(hwndBubble, "Quit");
                   WinSetWindowPos(hwndBubble, HWND_TOP, rectl.xLeft+hBut*16,rectl.yTop-hBut-24,60,22,
                   SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_PBWRITE), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_PBWRITE), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                        WinMapWindowPoints(hwndPBWrite, HWND_DESKTOP,&coords,1);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowText(hwndBubble, "Reply to Message");
                        WinSetWindowPos(hwndBubble, HWND_TOP, hBut,rectl.yTop-hBut-24, 160, 22,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                 }
                 coords.x = SHORT1FROMMP(parm1);
                 coords.y = SHORT2FROMMP(parm1);
                 WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_ZOOMIN), &coords, 1);
                 WinQueryWindowRect(WinWindowFromID(hwnd,ID_ZOOMIN), &rectl);
                 if (WinPtInRect(hab, &rectl, &coords))
                 {
                          WinMapWindowPoints(hwndPBZoomIn, HWND_DESKTOP,&coords,1);
                          WinQueryWindowRect(hwnd, &rectl);
                          WinSetWindowText(hwndBubble, "Zoom Mode");
                          WinSetWindowPos(hwndBubble, HWND_TOP, hBut*12-5,rectl.yTop-hBut-24, 100, 22,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                 }
                 coords.x = SHORT1FROMMP(parm1);
                 coords.y = SHORT2FROMMP(parm1);
                 WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_ZOOMOUT), &coords, 1);
                 WinQueryWindowRect(WinWindowFromID(hwnd,ID_ZOOMOUT), &rectl);
                 if (WinPtInRect(hab, &rectl, &coords))
                 {
                    WinMapWindowPoints(hwndPBZoomOut, HWND_DESKTOP,&coords,1);
                    WinQueryWindowRect(hwnd, &rectl);
                    WinSetWindowText(hwndBubble, "Normal Mode");
                    WinSetWindowPos(hwndBubble, HWND_TOP, hBut*12-5,rectl.yTop-hBut-24, 110, 22,
                          SWP_SIZE|SWP_MOVE|SWP_SHOW);
                 }
                 coords.x = SHORT1FROMMP(parm1);
                 coords.y = SHORT2FROMMP(parm1);
                 WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_LBKILL), &coords, 1);
                 WinQueryWindowRect(WinWindowFromID(hwnd,ID_LBKILL), &rectl);
                 if (WinPtInRect(hab, &rectl, &coords))
                 {
                    WinMapWindowPoints(hwndLBKill, HWND_DESKTOP,&coords,1);
                    WinPopupMenu(HWND_DESKTOP, hwnd, hwndPopKill, coords.x, coords.y, 0,PU_HCONSTRAIN|PU_VCONSTRAIN|
                    PU_MOUSEBUTTON1|PU_MOUSEBUTTON2|PU_KEYBOARD);
                 }
                 coords.x = SHORT1FROMMP(parm1);
                 coords.y = SHORT2FROMMP(parm1);
                 WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_LBALL), &coords, 1);
                 WinQueryWindowRect(WinWindowFromID(hwnd,ID_LBALL), &rectl);
                 if (WinPtInRect(hab, &rectl, &coords))
                 {
                      WinMapWindowPoints(hwndLBALL, HWND_DESKTOP,&coords,1);
                      WinPopupMenu(HWND_DESKTOP, hwnd, hwndPopAGroups, coords.x, coords.y, 0,PU_HCONSTRAIN|PU_VCONSTRAIN|
                                 PU_MOUSEBUTTON1|PU_MOUSEBUTTON2|PU_KEYBOARD);
                 }
                 coords.x = SHORT1FROMMP(parm1);
                 coords.y = SHORT2FROMMP(parm1);
                 WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_LB1WINDOW), &coords, 1);
                 WinQueryWindowRect(WinWindowFromID(hwnd,ID_LB1WINDOW), &rectl);
                 if (WinPtInRect(hab, &rectl, &coords))
                 {
                      WinMapWindowPoints(hwndLB, HWND_DESKTOP,&coords,1);
                      WinPopupMenu(HWND_DESKTOP, hwnd, hwndPopArticles, coords.x, coords.y, 0,PU_HCONSTRAIN|PU_VCONSTRAIN|
                                PU_MOUSEBUTTON1|PU_MOUSEBUTTON2|PU_KEYBOARD);
                 }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_LB2WINDOW), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_LB2WINDOW), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {
                     WinMapWindowPoints(hwndLB2, HWND_DESKTOP,&coords,1);
                     WinPopupMenu(HWND_DESKTOP, hwnd, hwndPopSGroups, coords.x, coords.y, 0,PU_HCONSTRAIN|PU_VCONSTRAIN|
                                  PU_MOUSEBUTTON1|PU_MOUSEBUTTON2|PU_KEYBOARD);
                }
                coords.x = SHORT1FROMMP(parm1);
                coords.y = SHORT2FROMMP(parm1);               //ID_LBUUQ
                WinMapWindowPoints(hwnd, WinWindowFromID(hwnd,ID_LBUUQ), &coords, 1);
                WinQueryWindowRect(WinWindowFromID(hwnd,ID_LBUUQ), &rectl);
                if (WinPtInRect(hab, &rectl, &coords))
                {                           //LBUUQueue
                     WinMapWindowPoints(hwndLBUUQueue, HWND_DESKTOP,&coords,1);
                     WinPopupMenu(HWND_DESKTOP, hwnd, hwndPopUUQ, coords.x, coords.y, 0,PU_HCONSTRAIN|PU_VCONSTRAIN|
                                  PU_MOUSEBUTTON1|PU_MOUSEBUTTON2|PU_KEYBOARD);
                }
        break;
        case WM_BUTTON2UP:
                WinSetWindowPos(hwndBubble, HWND_TOP, 0L,0L,0L,0L, SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinInvalidateRect(hwndLBTitle,NULL,FALSE);
                WinInvalidateRect(hwndLB2Title, NULL,FALSE);
                break;
        case WM_COMMAND:
                switch(SHORT1FROMMP(parm1)){
                case ID_LB2TITLE:
                if (BUSY==FALSE)
                {
                   WinQueryWindowRect (hwnd, &rectl);
                   if(Subed)
                   {
                      WinSetWindowText(hwndLB2Title, "All Newsgroups");
                      if(!LOADED)
                      {
                         stream=fopen("group.lst", "r");
                         if (stream==NULL)
                         {
                             LGRPS=WinMessageBox(HWND_DESKTOP, hwnd,
                             "Do you want to load newsgroups from server? (This may take a while)",
                             "Load Newsgroups", 0, MB_YESNO|MB_QUERY);
                             if (LGRPS==MBID_YES)
                             {
                                WinSetWindowText(hwndStatTxt, "Retrieving groups, Be Patient.");
                                BUSY=TRUE;
                                DoneL=FALSE;
                                _beginthread(GetGroup, NULL, 32768, (void *)hwnd);
                                break;
                             }
                             else break;
                         }
                         item=0;
                         fclose(stream);
                         BUSY=TRUE;
                         _beginthread(LGroup,NULL ,32768, (void *)hwnd);
                         LOADED=TRUE;
                      }
                      else
                      {
                         WinQueryWindowRect(hwnd, &rectl);
                         WinSetWindowPos(hwndLBALL, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                         SWP_SIZE|SWP_MOVE|SWP_SHOW);
                         /*
                         WinSetWindowPos(hwndLBALL, HWND_TOP,
                         rectl.xRight/3*2, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                         SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                         WinSetWindowPos(hwndLB2,HWND_TOP,0L,0L,0L,0L, SWP_SIZE|SWP_MOVE|SWP_SHOW);
                      }
                      Subed=FALSE;
                   }
                   else
                   {
                      Subed=TRUE;
                      WinQueryWindowRect(hwnd, &rectl);
                      WinSetWindowText(hwndLB2Title, "Subscribed Newsgroups");
                      WinSetWindowPos(hwndLB2, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                      SWP_SIZE|SWP_MOVE|SWP_SHOW);
                      /*
                      WinSetWindowPos(hwndLB2, HWND_TOP,
                      rectl.xRight/3*2, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                      SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                      WinSetWindowPos(hwndLBALL,HWND_TOP,0L,0L,0L,0L, SWP_SIZE|SWP_MOVE|SWP_SHOW);
                   }
                }
                break;
                case ID_LB1TITLE:
                if(ArtKil) {
                        WinSetWindowText(hwndLBTitle, "Kill File");
                        WinQueryWindowRect(hwnd, &rectl);
/*                        WinSetWindowPos(hwndLBKill, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3*2-5,
                                          rectl.yTop/2-hChar-hBut-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                        WinSetWindowPos(hwndLBKill, HWND_TOP,rectl.xRight/3, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);

                        WinSetWindowPos(hwndLB, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        SKill=TRUE;
                        ArtKil=FALSE;                   }
                else
                        {
                        ArtKil=TRUE;
                        SKill=FALSE;
                        WinSetWindowPos(hwndLBKill, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndLB, HWND_TOP,rectl.xRight/3, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        /*WinSetWindowPos(hwndLB, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3*2-5,
                                          rectl.yTop/2-hChar-hBut-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                        strcpy(titlstr, "Article List ");
                        strcat(titlstr, Head[0].Mid);
                        strcat(titlstr, "-");
                        strcat(titlstr, Head[b-1].Mid);
                        WinSetWindowText(hwndLBTitle, titlstr);
//                        WinSetWindowText(hwndLBTitle, "Article List");
                        }
                break;
                case MNOPEN:
                  item=WinQueryLboxSelectedItem(hwndLB2);
                  WinSendMsg(hwndLB2, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(groupname));
                  Drop(groupname,groupname,5);
                  WinSetWindowText(hwndStatTxt, groupname);
                  mki=strcspn(groupname, " ");
                  groupname[mki]='\0';
                  WinSendMsg(hwndLB, LM_DELETEALL,NULL,NULL);
                  _beginthread(GetHeaders, NULL, 32768, (void *)hwnd);
                break;
                case ID_MLETITLE:
                if(MsgUU) {
                        WinSetWindowText(hwndMLETitle, "UUDecoding Queue");
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndLBBlank, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndMLE, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndLBUUQueue, HWND_TOP,
                        rectl.xLeft+(rectl.xRight/3), rectl.yBottom+statusbar+1,rectl.xRight/3*2,rectl.yTop/2-hChar-statusbar+offset-20,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndUUText, HWND_TOP, rectl.xLeft+(rectl.xRight/3),rectl.yTop/2-hChar-20+offset,rectl.xRight/3*2,20,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndStatTxtUU, HWND_TOP,rectl.xLeft+3,rectl.yBottom+statusbar+5,rectl.xRight/3-6,20,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndPBUUDelete, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+30,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndPBUUPause, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+65,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndPBUUAbort, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+95,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndUUProgress, HWND_TOP, ((rectl.xRight/3)/2)-50, rectl.yBottom+statusbar+130, 80,80,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        MsgUU=FALSE;                    }
                else
                        {
                        MsgUU=TRUE;
                        WinSetWindowText(hwndMLETitle, "Current Message");
                        WinSetWindowPos(hwndLBUUQueue, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndUUText, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndUUProgress, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndPBUUDelete, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndPBUUPause, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndPBUUAbort, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndStatTxtUU, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinQueryWindowRect(hwnd, &rectl);
                        if(HideArt)
                            WinSetWindowPos(hwndLBBlank, HWND_TOP,rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop/2-hChar-statusbar+offset,
                            SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        else
                           WinSetWindowPos(hwndMLE, HWND_TOP,
                           rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop/2-hChar-statusbar+offset,
                           SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        }
                break;
                case MHABOUT:
                        WinDlgBox(HWND_DESKTOP, hwnd, ab_func, 0, DLG1, 0);
                break;
                case MOSET:
                case ID_PBSETT:
                WinDlgBox(HWND_DESKTOP, hwnd, SNotebook, 0, SETTNOTE, 0);
                break;
                case MNUUADDQ:
                case ID_PBUUQUEUE:
                        if(0!=WinSendMsg(hwndLB, LM_QUERYITEMCOUNT, 0,0))
                        {
                           item=WinQueryLboxSelectedItem(hwndLB);
                           do
                           {
                           WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                           articlei[0]='*';
                           WinSendMsg(hwndLB, LM_SETITEMTEXT,  MPFROM2SHORT(item,180), MPFROMP(articlei));
                           WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(item),(MPARAM)FALSE);
                           Drop(articlei, articlei,1);
                           sscanf(articlei, "%d", &mki2);
                           mki=0;
                           while(NULL==strstr(ListRead[mki].Groupname,groupname))
                           {
                              mki++;
                           }
                           NotThere=FALSE;
                           for(mki3=0;mki3<ListRead[mki].Count;mki3++)
                           {
                               if(mki2==ListRead[mki].ListRead[mki3])
                               {
                                   NotThere=TRUE;
                                   break;
                               }
                           }
                           if(!NotThere)
                           {
                              ListRead[mki].ListRead[ListRead[mki].Count]=mki2;
                              ListRead[mki].Count++;
                              mki4=mki;
                              mki=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(groupname));
                              WinSendMsg(hwndLB2, LM_QUERYITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                              sscanf(tmpstr4, "%d", &mki2);
                              mki2--;
                              if(mki2<=0)
                              {
                                 Large=0;
                                 for(mki3=0;mki3<ListRead[mki4].Count;mki3++)
                                 {
                                    if(Large<ListRead[mki4].ListRead[mki3])
                                       Large=ListRead[mki4].ListRead[mki3];
                                 }
                                 ListRead[mki4].ListRead[ListRead[mki4].Count]=abs(ListRead[mki4].ListRead[0]);
                                 ListRead[mki4].ListRead[0]=Large*(-1);
                                 ListRead[mki4].Count++;
                                 mki2=0;
                               }
                              sprintf(tmpstr4, "%d",mki2);
                              while(strlen(tmpstr4)<5)
                                strcat(tmpstr4, " ");
                              strcat(tmpstr4, groupname);
                              strcat(tmpstr4, " ");
                              WinSendMsg(hwndLB2, LM_SETITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                           }
                           item=(int)WinSendMsg(hwndLBUUQueue, LM_SEARCHSTRING, MPFROM2SHORT(LSS_CASESENSITIVE,LIT_FIRST),MPFROMP(articlei));
                           if (item==LIT_NONE)
                           {  qc++;
                              if (qc==1000)
                                qc=0;
                              WinSendMsg(hwndLBUUQueue, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(articlei));
                              i=strcspn(articlei, " ");
                              for(a=0;a<i;a++)
                                 UUNames[qc].MID[a]=articlei[a];
                                 strcpy(UUNames[qc].Group, groupname);
                                 UUNames[qc].MID[i]='\0';
                            }
                            item=WinQueryLboxSelectedItem(hwndLB);
                            }while (item!=LIT_NONE);
                           WinSetWindowText(hwndStatTxtUU, "Queuing article.");
                           if(!Decoding)
                              _beginthread(UUDecodePrep,NULL, 32768, (void *)hwnd);
                           Changed();
                        }
                break;
                case MMVHEAD:
                    WinDlgBox(HWND_DESKTOP, hwnd, VHeader, 0, VHEAD, 0);
                break;
                case RMKILL:
                   KItem2=WinQueryLboxSelectedItem(hwndLBKill);
                   WinSendMsg(hwndLBKill, LM_DELETEITEM, (MPARAM)KItem2, 0);
                   KItem2=(int)WinSendMsg(hwndLBKill, LM_QUERYITEMCOUNT, 0,0);
                   KFile2=fopen("newsbeat.kil", "w");
                   if(KFile2)
                   {
                      for(KCount2=0;KCount2<KItem2;KCount2++)
                      {
                          WinSendMsg(hwndLBKill, LM_QUERYITEMTEXT, MPFROM2SHORT(KCount2,256), MPFROMP(KString2));
                          fprintf(KFile2,"%s\n",KString2);
                      }
                      fprintf(KFile2, ".\n");
                      fclose(KFile2);
                   }
                break;
                case MMKILL:
                    WinDlgBox(HWND_DESKTOP, hwnd, AKillFile, 0, AKILL, 0);
                break;
                case MMRALL:
                case ID_PBMAAR:
                   Large=0;
                   b=(int)WinSendMsg(hwndLB, LM_QUERYITEMCOUNT,0,0);
                   WinEnableWindowUpdate(hwndLB, FALSE);
                   WinSendMsg(hwndLB, LM_DELETEALL,0,0);
                   item=0;
                   while(NULL==strstr(ListRead[item].Groupname,groupname))
                   {
                      item++;
                   }
                   itc=item;
                   for(item=0;item<b;item++)
                   {
                         strcpy(tmpspc, "*\0");
                         strcat(tmpspc, Head[item].Mid);
                         IGroup=tmpspc;
                         while(strlen(IGroup)<=8)
                           strcat(IGroup, " ");
                         strcat(IGroup, Head[item].Line);
                         while(strlen(IGroup)<=14)
                         strcat(IGroup, " ");
                         strcat(IGroup, Head[item].Subject);
                         strcat(IGroup, " (");
                         strcat(IGroup, Head[item].From);
                         strcat(IGroup, ")");
                         SInsert=TRUE;
                         for(mki=0;mki<=ListRead[itc].Count;mki++)
                         {
                           if(atoi(Head[item].Mid)==ListRead[itc].ListRead[mki])
                           {
                             SInsert=FALSE;break;
                           }
                         }
                         if(SInsert)
                         {
                              WinSendMsg(hwndLB, LM_INSERTITEM, MPFROMSHORT(0),IGroup);
                              sscanf(Head[item].Mid, "%d", &mki3);
                              NotThere=FALSE;
                              for(mki4=0;mki4<ListRead[itc].Count;mki4++)
                              {
                                 if(mki3==ListRead[itc].ListRead[mki4])
                                 {
                                    NotThere=TRUE;
                                    break;
                                 }
                               }
                               if(!NotThere)
                               {
                                    ListRead[itc].ListRead[ListRead[itc].Count]=mki3;
                                    ListRead[itc].Count++;
                                    SInsert=FALSE;
                               }
                           }
                   }
                   Large=0;
                   for(mki=0;mki<ListRead[itc].Count;mki++)
                   {
                       if(Large<ListRead[itc].ListRead[mki])
                       {
                         Large=ListRead[itc].ListRead[mki];
                       }
                   }
                   ListRead[itc].ListRead[ListRead[itc].Count]=abs(ListRead[itc].ListRead[0]);
                   ListRead[itc].ListRead[0]=Large*-1;
                   ListRead[itc].Count++;
                   mki=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(groupname));
                   WinSendMsg(hwndLB2, LM_QUERYITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                   sprintf(tmpstr4, "0");
                   while(strlen(tmpstr4)<5)
                      strcat(tmpstr4, " ");
                   strcat(tmpstr4, groupname);
                   strcat(tmpstr4, " ");
                   WinSendMsg(hwndLB2, LM_SETITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                   WinEnableWindowUpdate(hwndLB, TRUE);
                   if(Connected)
                      Changed();
                break;
                case MMUALL:
                case ID_PBMAAUR:
                break;
                case MMUCUR:
                case ID_PBMAUR:
                   item=WinQueryLboxSelectedItem(hwndLB);
                   WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                   if(articlei[0]=='*')
                   {
                      articlei[0]=' ';
                      WinSendMsg(hwndLB, LM_SETITEMTEXT,  MPFROM2SHORT(item,180), MPFROMP(articlei));
                      WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(item),(MPARAM)FALSE);
                      Drop(articlei, articlei, 1);
                      sscanf(articlei, "%d", &mki2);
                      mki=0;
                      while(NULL==strstr(ListRead[mki].Groupname,groupname))
                      {
                         mki++;
                      }
                      for(mki3=0;mki3<ListRead[mki].Count;mki3++)
                      {
                         if(mki2==ListRead[mki].ListRead[mki3])
                         {
                           ListRead[mki].ListRead[mki3]=0;
                         }
                      }
                      mki4=mki;
                      mki=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(groupname));
                      WinSendMsg(hwndLB2, LM_QUERYITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                      sscanf(tmpstr4, "%d", &mki2);
                      mki2++;
                      sprintf(tmpstr4, "%d",mki2);
                      while(strlen(tmpstr4)<5)
                         strcat(tmpstr4, " ");
                      strcat(tmpstr4, groupname);
                      strcat(tmpstr4, " ");
                      WinSendMsg(hwndLB2, LM_SETITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                      if(Connected)
                      Changed();
                   }
                break;
                case ID_ZALL:
                        if(!LOADED)
                        {
                           stream=fopen("group.lst", "r");
                           if (stream==NULL)
                           {
                               LGRPS=WinMessageBox(HWND_DESKTOP, hwnd,
                               "Do you want to load newsgroups from server? (This may take a while)",
                               "Load Newsgroups", 0, MB_YESNO|MB_QUERY);
                               if (LGRPS==MBID_YES)
                               {
                                    WinSetWindowText(hwndStatTxt, "Retrieving groups, Be Patient.");
                                    BUSY=TRUE;
                                    DoneL=FALSE;
                                    _beginthread(GetGroup, NULL, 32768, (void *)hwnd);
                                    break;
                               }
                               else break;
                            }
                            item=0;
                            fclose(stream);
                            BUSY=TRUE;
                            _beginthread(LGroup,NULL ,32768, (void *)hwnd);
                            LOADED=TRUE;
                        }
                        WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)1,0);
                        WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)0,0);
                        WinSetWindowPos(hwndLB2, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLB, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBUUQueue, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBKill, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndMLE, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndLBALL, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        ZState=2;
                break;
                case ID_ZKILL:
                        WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)1,0);
                        WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)0,0);
                        WinSetWindowPos(hwndLB, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLB2, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBALL, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBUUQueue, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndMLE, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        ZState=4;
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndLBKill, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);


                break;
                case ID_ZMSG:
                        WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)1,0);
                        WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)0,0);
                        WinSetWindowPos(hwndLB, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLB2, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBALL, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBUUQueue, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBKill, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndMLE, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        ZState=3;
                break;
                case ID_ZGROUPS:
                        WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)1,0);
                        WinSetWindowPos(hwndLB, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBUUQueue, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndMLE, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBKill, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBALL, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndLB2, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        ZState=0;
                break;
                case ID_ZUULIST:
                        WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)1,0);
                        WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)0,0);
                        WinSetWindowPos(hwndMLE, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBKill, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLB2, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLB, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBALL, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        ZState=5;
                break;
                case ID_ZARTICLE:
                        WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)1,0);
                        WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)0,0);
                        WinSetWindowPos(hwndLB2, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBALL, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndMLE, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBKill, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBUUQueue, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndLB, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        ZState=1;
                break;
                case ID_ZOOMIN:
                  if(!ZOOMED)
                  {
                        ZOOMED=TRUE;
                        WinSetWindowPos(hwndMLETitle,HWND_TOP,0,0,0,0,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBBlank, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBKill,  HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndMLE, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndPBUUDelete, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBUUQueue, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndUUText, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndPBUUPause, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndUUProgress, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                        WinSetWindowPos(hwndPBUUAbort, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndStatTxtUU, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBALL,HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLB,HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLB2,HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLB2Title, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndLBTitle, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndLB2, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZGroups, HWND_TOP, rectl.xLeft, rectl.yTop-hBut-5-hChar,rectl.xRight/3,hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZAll, HWND_TOP, rectl.xRight/3, rectl.yTop-hBut-5-hChar,rectl.xRight/3, hChar, SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZKill, HWND_TOP, rectl.xRight/3*2, rectl.yTop-hBut-5-hChar, rectl.xRight/3, hChar, SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZArticle, HWND_TOP, rectl.xLeft,rectl.yTop-hBut-hChar*2-5, rectl.xRight/3, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZMsg,HWND_TOP, rectl.xRight/3,rectl.yTop-hBut-hChar*2-5, rectl.xRight/3, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZUUList,HWND_TOP, rectl.xRight/3*2,rectl.yTop-hBut-hChar*2-5, rectl.xRight/3, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)1,0);
                        WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)0,0);
                        WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)0,0);

                  }
                break;
                case ID_ZOOMOUT:
                  if(ZOOMED)
                  {
                        ZOOMED=FALSE;
                        WinSetWindowPos(hwndZGroups, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZAll, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZKill, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZArticle, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZMsg, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinSetWindowPos(hwndZUUList, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        WinQueryWindowRect(hwnd, &rectl);
                        WinSetWindowPos(hwndMLETitle, HWND_TOP,rectl.xLeft,rectl.yTop/2-hChar+offset,rectl.xRight,hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        if(!MsgUU)
                        {
                           WinSetWindowPos(hwndLBBlank, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndMLE, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndLBUUQueue, HWND_TOP,
                              rectl.xLeft+(rectl.xRight/3), rectl.yBottom+statusbar+1,rectl.xRight/3*2,rectl.yTop/2-hChar-statusbar+offset-20,
                              SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndUUText, HWND_TOP, rectl.xLeft+(rectl.xRight/3),rectl.yTop/2-hChar-20+offset,rectl.xRight/3*2,20,
                              SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndStatTxtUU, HWND_TOP,rectl.xLeft+3,rectl.yBottom+statusbar+5,rectl.xRight/3-6,20,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndPBUUDelete, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+30,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndPBUUPause, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+65,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndPBUUAbort, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+95,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndUUProgress, HWND_TOP, ((rectl.xRight/3)/2)-30, rectl.yBottom+statusbar+140, 60,60,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        }
                        else
                        {
                          if(HideArt)
                             WinSetWindowPos(hwndLBBlank, HWND_TOP,
                                rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop/2-hChar-statusbar+offset,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                          else
                             WinSetWindowPos(hwndMLE, HWND_TOP,
                                rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop/2-hChar-statusbar+offset,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                             WinSetWindowPos(hwndPBUUDelete, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                             WinSetWindowPos(hwndLBUUQueue, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                             WinSetWindowPos(hwndUUText, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                             WinSetWindowPos(hwndPBUUPause, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                             WinSetWindowPos(hwndUUProgress, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                             WinSetWindowPos(hwndPBUUAbort, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                             WinSetWindowPos(hwndStatTxtUU, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        }
                        WinSetWindowPos(hwndLBTitle, HWND_TOP,rectl.xRight/3, rectl.yTop-hChar-hBut, rectl.xRight/3*2-5, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                      //  WinSetWindowPos(hwndLBTitle, HWND_TOP,rectl.xLeft, rectl.yTop-hChar-hBut, rectl.xRight/3*2-5, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        if(!HideArt)
                            WinSetWindowPos(hwndLB, HWND_TOP,rectl.xRight/3, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
                            SWP_SIZE|SWP_MOVE|SWP_SHOW);

                          /* WinSetWindowPos(hwndLB, HWND_TOP,
                              rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
                              SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           WinSetWindowPos(hwndLB2Title, HWND_TOP,
                              rectl.xRight/3*2, rectl.yTop-hChar-hBut, rectl.xRight/3,hChar,
                              SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                           WinSetWindowPos(hwndLB2Title, HWND_TOP,rectl.xLeft, rectl.yTop-hChar-hBut, rectl.xRight/3, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                           if (Subed)
                           {
                              WinQueryWindowRect(hwnd, &rectl);
                              WinSetWindowPos(hwndLB2, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                              SWP_SIZE|SWP_MOVE|SWP_SHOW);

                              /*
                              WinSetWindowPos(hwndLB2, HWND_TOP,
                                 rectl.xRight/3*2, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                                 SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                           }
                           else
                           {
                              WinQueryWindowRect(hwnd, &rectl);
                              WinSetWindowPos(hwndLBALL, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                              SWP_SIZE|SWP_MOVE|SWP_SHOW);

                              /*
                              WinSetWindowPos(hwndLBALL, HWND_TOP,
                                 rectl.xRight/3*2, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                                 SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                           }
                              WinSetWindowPos(hwndStatTxt, HWND_TOP,
                                 rectl.xLeft, rectl.yBottom,rectl.xRight/2,statusbar,
                                 SWP_SIZE|SWP_MOVE|SWP_SHOW);
                  }
                break;
                case MMRCUR:
                case ID_PBMAR:
                {
                   item=WinQueryLboxSelectedItem(hwndLB);
                   WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                   articlei[0]='*';
                   WinSendMsg(hwndLB, LM_SETITEMTEXT,  MPFROM2SHORT(item,180), MPFROMP(articlei));
                   WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(item),(MPARAM)FALSE);
                   Drop(articlei, articlei, 1);
                   sscanf(articlei, "%d", &mki2);
                   mki=0;
                   while(NULL==strstr(ListRead[mki].Groupname,groupname))
                   {
                      mki++;
                   }
                   NotThere=FALSE;
                   for(mki3=0;mki3<ListRead[mki].Count;mki3++)
                   {
                        if(mki2==ListRead[mki].ListRead[mki3])
                        {
                           NotThere=TRUE;
                           break;
                        }
                   }
                   if(!NotThere)
                   {
                      ListRead[mki].ListRead[ListRead[mki].Count]=mki2;
                      ListRead[mki].Count++;
                   mki4=mki;
                   mki=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(groupname));
                   WinSendMsg(hwndLB2, LM_QUERYITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                   sscanf(tmpstr4, "%d", &mki2);
                   mki2--;
                   if(mki2<=0)
                   {
                      Large=0;
                      for(mki3=0;mki3<ListRead[mki4].Count;mki3++)
                      {
                          if(Large<ListRead[mki4].ListRead[mki3])
                             Large=ListRead[mki4].ListRead[mki3];
                      }
                      ListRead[mki4].ListRead[ListRead[mki4].Count]=abs(ListRead[mki4].ListRead[0]);
                      ListRead[mki4].ListRead[0]=Large*(-1);
                      ListRead[mki4].Count++;
                      mki2=0;
                    }
                   sprintf(tmpstr4, "%d",mki2);
                   while(strlen(tmpstr4)<5)
                      strcat(tmpstr4, " ");
                   strcat(tmpstr4, groupname);
                   strcat(tmpstr4, " ");
                   WinSendMsg(hwndLB2, LM_SETITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                   if(Connected)
                   Changed();
                   }
                }
                break;
                case UUABALL:
                case ID_PBUUABORT:
                    Abort=TRUE;
                    WinSetWindowText(hwndStatTxtUU, "Aborting UUDecode.");
                break;
                case UUDELI:
                case ID_PBUUDEL:
                        item=WinQueryLboxSelectedItem(hwndLBUUQueue);
                        if(item!=0)
                            WinSendMsg(hwndLBUUQueue, LM_DELETEITEM, (MPARAM)item, 0);
                break;
                case UUPAUSE:
                case ID_PBUUPAUSE:
                     if(Paused)
                     {
                        Paused=FALSE;
                        WinSetWindowText(hwndStatTxtUU, "");
                     }
                     else
                     {
                        Paused=TRUE;
                        WinSetWindowText(hwndStatTxtUU, "Paused.");
                     }
                break;
                case MMREPLY:
                case ID_PBWRITE:
                        New=FALSE;
                        item=WinQueryLboxSelectedItem(hwndLB);
                        WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                        Drop(articlei,articlei, 1);
                        i=strcspn(articlei, " ");
                        for(a=0;a<i;a++)
                           article[a]=articlei[a];
                        WinDlgBox(HWND_DESKTOP,HWND_DESKTOP,editor_func,0,EDITOR,0);
                break;
                case MMNEW:
                case MMPOST:
                case ID_PBNEWL:
                        New=TRUE;
                        WinDlgBox(HWND_DESKTOP,HWND_DESKTOP,editor_func,0,EDITOR,0);
                break;
                case MOSERVER:
                _beginthread(Connect,NULL ,32768, (void *)hwnd);
                break;
                case MNREFRESH:
                   LGRPS=WinMessageBox(HWND_DESKTOP, hwnd,
                   "Are you sure? Loading newsgroups can take a while.",
                   "Re-Load Newsgroups", 0, MB_YESNO|MB_QUERY);
                   if (LGRPS==MBID_YES)
                   {
                      WinSetWindowText(hwndStatTxt, "Retrieving groups, Be Patient.");
                      BUSY=TRUE;
                      WinSendMsg(hwndLBALL, LM_DELETEALL, 0,0);
                      _beginthread(GetGroup, NULL, 32768, (void *)hwnd);
                      break;
                   }
                   else
                break;
                case MNUNSUB:
                {
                   int idem;
                   idem=WinQueryLboxSelectedItem(hwndLB2);
                   WinSendMsg(hwndLB2, LM_QUERYITEMTEXT, MPFROM2SHORT(idem,1000), MPFROMP(groupd));
                   mki=0;
                   while(NULL==strstr(groupd,ListRead[mki].Groupname))
                   {
                      mki++;
                   }
                   ListRead[mki].Groupname[0]='\0';
                   WinSendMsg(hwndLB2, LM_DELETEITEM, MPFROMSHORT(idem),(MPARAM)NULL);
                   if(Connected)
                   Changed();
                   }
                break;
                case MNSUBC:
                     SGItem=WinQueryLboxSelectedItem(hwndLBALL);
                     WinSendMsg(hwndLBALL, LM_QUERYITEMTEXT, MPFROM2SHORT(SGItem,180), MPFROMP(groupname));
                     _beginthread(Subscribe, NULL, 32768, (void *)hwnd);
                break;
                case MMCOPY:
                case ID_PBCOPY:
                        WinSendMsg(hwndMLE, MLM_COPY, 0L, 0L);
                break;
                case MOLOGOUT:
                   DosSetCurrentDir("..");
                break;
                case MOLOGIN:
                stream=fopen("user.lst", "r");
                if (stream) {WinDlgBox(HWND_DESKTOP,hwnd,Login_Func,0,LOGIN,0); fclose(stream);}
                break;
                case MMSEARCH:
                   hwndSDlg=WinLoadDlg(HWND_DESKTOP, HWND_DESKTOP, MSearch, 0L, FMESSAGE, NULL);
                break;
                case MNSEARCH:
                if (LOADED)
                {
                   WinDlgBox(HWND_DESKTOP,hwnd,Search_Func,0,FGROUP,0);
                   SGItem=(int)WinSendMsg(hwndLBALL, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(SGroup));
                   if(SGItem!=LIT_NONE)
                       WinSendMsg(hwndLBALL, LM_SETTOPINDEX, MPFROMP(SGItem),0);
                }
                else
                    WinMessageBox(HWND_DESKTOP, hwnd, "To search, you must have newsgroups loaded.","Newsgroups Not Loaded.", 0, MB_OK|MB_ERROR);
                break;
                case MNSUB:
                  if (LOADED)
                  {
                     WinDlgBox(HWND_DESKTOP,hwnd,Subscribe_Func,0,SGROUP,0);
                     SGItem=(int)WinSendMsg(hwndLBALL, LM_SEARCHSTRING, MPFROM2SHORT(LSS_CASESENSITIVE,LIT_FIRST),MPFROMP(SGroup));
                     if(SGItem!=LIT_NONE)
                     {
                         SGItem=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_CASESENSITIVE,LIT_FIRST),MPFROMP(SGroup));
                         if (SGItem==LIT_NONE)
                            WinSendMsg(hwndLB2, LM_INSERTITEM, MPFROMSHORT(LIT_SORTASCENDING), MPFROMP(SGroup));
                     }
                   }
                   else
                      WinMessageBox(HWND_DESKTOP, hwnd, "You must load newsgroups into memory, click on Subscribed Newsgroups to load.","Newsgroups Not Loaded.", 0, MB_OK|MB_ERROR);
                break;
                case MMUSER:
                WinDlgBox(HWND_DESKTOP,hwnd,Edit_Func,0,USEREDIT,0);
                break;
                case ID_PBEXPLORE:
                {
                   STARTDATA StartData;
                   ULONG SessID;
                   PID PID;
                   UCHAR PgmTitle[40];
                   UCHAR PgmName[256];
                   UCHAR PgmInputs[200];
                   UCHAR ObjBuf[100];
                   int InsNull,rc;
                   LONG lStart, cch;
                   CHAR szB[500];
                   CHAR pObjname[128];
                   RESULTCODES result;
                   char CmmdLine[500];
                   InsNull=strlen(Browser)+1;
                   memset(&szB, 0, sizeof(szB));
                   memset(&CmmdLine, 0,sizeof(CmmdLine));
                   lStart=(LONG)WinSendMsg(hwndMLE, MLM_QUERYSEL,(MPARAM)MLFQS_MINSEL, (MPARAM)0L);
                   cch=(LONG)WinSendMsg(hwndMLE, MLM_QUERYSEL,(MPARAM)MLFQS_MAXSEL, (MPARAM)0L);
                   WinSendMsg(hwndMLE, MLM_SETIMPORTEXPORT, (MPARAM)szB, (MPARAM)cch-lStart);
                   WinSendMsg(hwndMLE, MLM_EXPORT, (MPARAM)&lStart, (MPARAM)&cch);
//                 sprintf(CmmdLine, "%s  %s %s",Browser,Params, szB);
                   StartData.Length=sizeof(STARTDATA);
                   StartData.Related=SSF_RELATED_INDEPENDENT;
                   StartData.FgBg=SSF_FGBG_FORE;
                   StartData.TraceOpt=SSF_TRACEOPT_NONE;
                   strcpy(PgmTitle, "Web Browser");
                   StartData.PgmTitle=PgmTitle;
                   strcpy(PgmName, Browser);
                   StartData.PgmName=PgmName;
                   strcpy(PgmInputs, Params);
                   strcat(PgmInputs, " ");
                   strcat(PgmInputs, szB);
                   StartData.PgmInputs=PgmInputs;
                   StartData.TermQ=0;
                   StartData.Environment=0;
                   StartData.InheritOpt=SSF_INHERTOPT_SHELL;
                   StartData.SessionType=SSF_TYPE_DEFAULT;
                   StartData.IconFile=0;
                   StartData.PgmHandle=0;
                   StartData.PgmControl=SSF_CONTROL_VISIBLE|SSF_CONTROL_MAXIMIZE;
                   StartData.InitXPos=30;
                   StartData.InitYPos=40;
                   StartData.InitXSize=200;
                   StartData.InitYSize=140;
                   StartData.Reserved=0;
                   StartData.ObjectBuffer=ObjBuf;
                   StartData.ObjectBuffLen=100;
                   DosStartSession(&StartData, &SessID, &PID);/*
                   CmmdLine[InsNull]=0;
                   DosExecPgm(pObjname, sizeof(pObjname), EXEC_BACKGROUND,CmmdLine, NULL, &result,Browser);*/
                }
                break;
                case MNUPDATE:
                _beginthread(Connect,NULL ,32768, (void *)hwnd);
                break;
                case ID_PBSAVE:
                case MMSAVE:
                        memset(&fd, 0, sizeof(FILEDLG));
                        fd.cbSize=sizeof(FILEDLG);
                        fd.fl=FDS_CENTER|FDS_SAVEAS_DIALOG;
                        strcpy(fd.szFullFile, "message.txt");
                        fd.pszTitle=fdTitle;
                        fdlg=WinFileDlg(HWND_DESKTOP,hwnd,&fd);
                        if(fdlg && (fd.lReturn==DID_OK))
                        {
                        /*
                        FILE *sarf, *sawf;
                        char satstring[MAXLINE];
                        BOOL APPEND=FALSE;
                        */
                        sarf=fopen(fd.szFullFile, "r");
                        if (sarf)
                        {
                           fclose(sarf);
                           WinDlgBox(HWND_DESKTOP, hwnd, App_Func, 0, APPENDDLG, 0);
                           sarf=fopen("head.txt", "r");
                           if(sarf)
                           {
                              if (APPEND==0)
                                 sawf=fopen(fd.szFullFile, "w");
                              if (APPEND==1)
                                 sawf=fopen(fd.szFullFile, "a");
                              if (sawf)
                              {
                                 fputs("\n---------------------------------------------------------\n", sawf);
                                 while(fgets(satstring, MAXLINE, sarf))
                                 {
                                    sap=strcspn(satstring, "\r");
                                    if (sap<strlen(satstring))
                                    {
                                      satstring[sap]='\n';
                                      satstring[sap+1]='\0';
                                    }
                                    fputs(satstring, sawf);
                                 }
                                 fclose(sarf);
                                 sarf=fopen("article.txt", "r");
                                 if(sarf)
                                 {
                                    while(fgets(satstring, MAXLINE, sarf))
                                    {
                                       sap=strcspn(satstring, "\r");
                                       if (sap<strlen(satstring))
                                       {
                                         satstring[sap]='\n';
                                         satstring[sap+1]='\0';
                                       }
                                       fputs(satstring, sawf);
                                 }
                                 }
                                 fclose(sawf);
                                 WinMessageBox(HWND_DESKTOP, hwnd, fd.szFullFile, "File Saved",0,0);
                              }
                              else
                                 WinMessageBox(HWND_DESKTOP, hwnd, fd.szFullFile, "Error, File Not Saved",0,0);
                              fclose(sarf);
                           }
                           else
                             WinMessageBox(HWND_DESKTOP, hwnd, fd.szFullFile, "Error, File Not Saved",0,0);
                        }
                        else
                        {
                            sarf=fopen("head.txt", "r");
                            if(sarf)
                            {
                               sawf=fopen(fd.szFullFile, "w");
                               while(fgets(satstring, MAXLINE, sarf))
                               {
                                  sap=strcspn(satstring, "\r");
                                  if (sap<strlen(satstring))
                                  {
                                     satstring[sap]='\n';
                                     satstring[sap+1]='\0';
                                  }
                                  fputs(satstring, sawf);
                                }
                                fclose(sarf);
                                sarf=fopen("article.txt", "r");
                                if(sarf)
                                {
                                   while(fgets(satstring, MAXLINE, sarf))
                                   {
                                      sap=strcspn(satstring, "\r");
                                      if (sap<strlen(satstring))
                                      {
                                         satstring[sap]='\n';
                                         satstring[sap+1]='\0';
                                      }
                                      fputs(satstring, sawf);
                                    }
                                 }
                                 fclose(sawf);
                                 fclose(sarf);
                            }
                            WinMessageBox(HWND_DESKTOP, hwnd, fd.szFullFile, "File Saved",0,0);
                        }

                        }
                        break;
                case MMPRINT:
                case ID_PBPRINT:
                    DosCopy("article.txt", "prn", 0L);
                break;
                case ID_PBQUIT:
                case MMEXIT: WinPostMsg(hwnd, WM_CLOSE, 0,0); break;

                case WM_ERASEBACKGROUND: return (MRESULT)TRUE;
                default:return WinDefWindowProc(hwnd, msg, parm1, parm2);
                }
        case WM_PAINT:
        hps = WinBeginPaint (hwnd,0,0);
        WinQueryWindowRect (hwnd, &rectl);
        WinFillRect (hps, &rectl, CLR_PALEGRAY);
        GpiSetColor(hps,CLR_BLACK);
        scoords.x=rectl.xRight/2+10;
        scoords.y=2;    GpiSetCurrentPosition(hps, &scoords);
        bcoords.x=rectl.xRight-10;
        bcoords.y=18;
        GpiBox(hps,DRO_OUTLINEFILL,&bcoords,1,1);
        WinEndPaint (hps);

        break;
        case WM_SIZE:{
                WinQueryWindowRect(hwnd, &rectl);
                if(LBUTTONS==TRUE)
                {
                hBut=38;
                WinSetWindowPos(hwndPBNewL, HWND_TOP, rectl.xLeft, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBWrite, HWND_TOP, rectl.xLeft+hBut, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBPrint, HWND_TOP, rectl.xLeft+hBut*2+10,rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBUUQueue, HWND_TOP, rectl.xLeft+hBut*3+10,rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBSave, HWND_TOP, rectl.xLeft+hBut*4+10, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBCopy, HWND_TOP, rectl.xLeft+hBut*5+10, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBMarkRead, HWND_TOP, rectl.xLeft+hBut*6+20, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBMarkUnread, HWND_TOP, rectl.xLeft+hBut*7+20, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBMarkAllRead, HWND_TOP, rectl.xLeft+hBut*8+20, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBMarkAllUnread, HWND_TOP, rectl.xLeft+hBut*9+20, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBExplore, HWND_TOP, rectl.xLeft+hBut*10+30, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBZoomIn, HWND_TOP, rectl.xLeft+hBut*11+30, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBZoomOut, HWND_TOP, rectl.xLeft+hBut*12+30, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBSett, HWND_TOP, rectl.xLeft+hBut*13+40, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBHelp, HWND_TOP, rectl.xLeft+hBut*14+40,rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBQuit, HWND_TOP, rectl.xLeft+hBut*15+40, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                else
                {
                hBut=24;
                WinSetWindowPos(hwndPBNewL, HWND_TOP, rectl.xLeft, rectl.yTop-hBut, hBut, hBut,
                               SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBWrite, HWND_TOP, rectl.xLeft+hBut, rectl.yTop-hBut, hBut, hBut,
                               SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBPrint, HWND_TOP, rectl.xLeft+hBut*2+10,rectl.yTop-hBut, hBut, hBut,
                               SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBUUQueue, HWND_TOP, rectl.xLeft+hBut*3+10,rectl.yTop-hBut, hBut, hBut,
                               SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBSave, HWND_TOP, rectl.xLeft+hBut*4+10, rectl.yTop-hBut, hBut, hBut,
                               SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBCopy, HWND_TOP, rectl.xLeft+hBut*5+10, rectl.yTop-hBut, hBut, hBut,
                               SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBMarkRead, HWND_TOP, rectl.xLeft+hBut*6+20, rectl.yTop-hBut, hBut, hBut,
                               SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBMarkUnread, HWND_TOP, rectl.xLeft+hBut*7+20, rectl.yTop-hBut, hBut, hBut,
                               SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBMarkAllRead, HWND_TOP, rectl.xLeft+hBut*8+20, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBMarkAllUnread, HWND_TOP, rectl.xLeft+hBut*9+20, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBExplore, HWND_TOP, rectl.xLeft+hBut*10+30, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBZoomIn, HWND_TOP, rectl.xLeft+hBut*11+30, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBZoomOut, HWND_TOP, rectl.xLeft+hBut*12+30, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBSett, HWND_TOP, rectl.xLeft+hBut*13+40, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBHelp, HWND_TOP, rectl.xLeft+hBut*14+40,rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndPBQuit, HWND_TOP, rectl.xLeft+hBut*15+40, rectl.yTop-hBut, hBut, hBut,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                if(!ZOOMED)
                {
                   WinSetWindowPos(hwndMLETitle, HWND_TOP,
                                rectl.xLeft,rectl.yTop/2-hChar+offset,rectl.xRight,hChar,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                   if(!MsgUU)
                   {
                     WinSetWindowPos(hwndLBBlank, HWND_TOP,0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                     WinSetWindowPos(hwndMLE, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                     WinSetWindowPos(hwndLBUUQueue, HWND_TOP,
                       rectl.xLeft+(rectl.xRight/3), rectl.yBottom+statusbar+1,rectl.xRight/3*2,rectl.yTop/2-hChar-statusbar+offset-20,
                       SWP_SIZE|SWP_MOVE|SWP_SHOW);
                     WinSetWindowPos(hwndUUText, HWND_TOP, rectl.xLeft+(rectl.xRight/3),rectl.yTop/2-hChar-20+offset,rectl.xRight/3*2,20,
                       SWP_SIZE|SWP_MOVE|SWP_SHOW);
                     WinSetWindowPos(hwndStatTxtUU, HWND_TOP,rectl.xLeft+3,rectl.yBottom+statusbar+5,rectl.xRight/3-6,20,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                     WinSetWindowPos(hwndPBUUDelete, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+30,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                     WinSetWindowPos(hwndPBUUPause, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+65,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                     WinSetWindowPos(hwndPBUUAbort, HWND_TOP, rectl.xLeft+10,rectl.yBottom+statusbar+95,rectl.xRight/3-20,30,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                     WinSetWindowPos(hwndUUProgress, HWND_TOP, ((rectl.xRight/3)/2)-30, rectl.yBottom+statusbar+140, 60,60,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                   }
                   else
                   {
                      if(HideArt)
                        WinSetWindowPos(hwndLBBlank, HWND_TOP,
                        rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop/2-hChar-statusbar+offset,
                        SWP_SIZE|SWP_MOVE|SWP_SHOW);
                      else
                       WinSetWindowPos(hwndMLE, HWND_TOP,
                       rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop/2-hChar-statusbar+offset,
                       SWP_SIZE|SWP_MOVE|SWP_SHOW);
                    WinSetWindowPos(hwndPBUUDelete, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                    WinSetWindowPos(hwndLBUUQueue, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                    WinSetWindowPos(hwndUUText, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                    WinSetWindowPos(hwndPBUUPause, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                    WinSetWindowPos(hwndUUProgress, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_HIDE);
                    WinSetWindowPos(hwndPBUUAbort, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                    WinSetWindowPos(hwndStatTxtUU, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                  }
                  WinSetWindowPos(hwndLBTitle, HWND_TOP,rectl.xRight/3, rectl.yTop-hChar-hBut, rectl.xRight/3*2-5, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                  /*
                WinSetWindowPos(hwndLBTitle, HWND_TOP,
                                rectl.xLeft, rectl.yTop-hChar-hBut, rectl.xRight/3*2-5, hChar,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                if(!HideArt)
                WinSetWindowPos(hwndLB, HWND_TOP,rectl.xRight/3, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
                SWP_SIZE|SWP_MOVE|SWP_SHOW);

                /*
                 WinSetWindowPos(hwndLB, HWND_TOP,
                                   rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
                                   SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                WinSetWindowPos(hwndLB2Title, HWND_TOP,rectl.xLeft, rectl.yTop-hChar-hBut, rectl.xRight/3, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);

        /*        WinSetWindowPos(hwndLB2Title, HWND_TOP,
                                rectl.xRight/3*2, rectl.yTop-hChar-hBut, rectl.xRight/3,hChar,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                if (Subed)
                {WinQueryWindowRect(hwnd, &rectl);
                WinSetWindowPos(hwndLB2, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                /*
                WinSetWindowPos(hwndLB2, HWND_TOP,
                                rectl.xRight/3*2, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                                }
                else
                {
                WinQueryWindowRect(hwnd, &rectl);
                WinSetWindowPos(hwndLBALL, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                /*
                WinSetWindowPos(hwndLBALL, HWND_TOP,
                                rectl.xRight/3*2, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                }
                WinSetWindowPos(hwndStatTxt, HWND_TOP,
                                rectl.xLeft, rectl.yBottom,rectl.xRight/2,statusbar,
                                SWP_SIZE|SWP_MOVE|SWP_SHOW);
                if(SKill)
                {
                   WinQueryWindowRect(hwnd, &rectl);
                   WinSetWindowPos(hwndLBKill, HWND_TOP,rectl.xRight/3, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                   /*
                   WinSetWindowPos(hwndLBKill, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3*2-5,
                                   rectl.yTop/2-hChar-hBut-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                }
                else
                {
                 WinQueryWindowRect(hwnd, &rectl);
                 WinSetWindowPos(hwndLB, HWND_TOP,rectl.xRight/3, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                 /*
                 WinSetWindowPos(hwndLB, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3*2-5,
                                 rectl.yTop/2-hChar-hBut-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
                }
                }
                else
                {
                if(ZState==0)
                   WinSetWindowPos(hwndLB2, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                if(ZState==1)
                   WinSetWindowPos(hwndLB, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                if(ZState==2)
                   WinSetWindowPos(hwndLBALL, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                if(ZState==3)
                   WinSetWindowPos(hwndMLE, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                if(ZState==4)
                   WinSetWindowPos(hwndLBKill, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                if(ZState==5)
                {
                   WinSetWindowPos(hwndLBUUQueue, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight/3*2, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
                WinSetWindowPos(hwndZGroups, HWND_TOP, rectl.xLeft, rectl.yTop-hBut-5-hChar,rectl.xRight/3,hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndZAll, HWND_TOP, rectl.xRight/3, rectl.yTop-hBut-5-hChar,rectl.xRight/3, hChar, SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndZKill, HWND_TOP, rectl.xRight/3*2, rectl.yTop-hBut-5-hChar, rectl.xRight/3, hChar, SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndZArticle, HWND_TOP, rectl.xLeft,rectl.yTop-hBut-hChar*2-5, rectl.xRight/3, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndZMsg,HWND_TOP, rectl.xRight/3,rectl.yTop-hBut-hChar*2-5, rectl.xRight/3, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinSetWindowPos(hwndZUUList,HWND_TOP, rectl.xRight/3*2,rectl.yTop-hBut-hChar*2-5, rectl.xRight/3, hChar,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                }
        break;
        }

        case WM_ERASEBACKGROUND:
                return((MRESULT) TRUE);
        case WM_CLOSE:{ int kj;
                if(Change)
                {
                stream2s=fopen("group.sub", "w");
                for(j=0;j<SubGroup;j++)
                {
                   if(ListRead[j].Groupname[0]!='\0')
                   {
                      fprintf(stream2s,"%s\n", ListRead[j].Groupname);
                      for(kj=0;kj<ListRead[j].Count;kj++)
                      {
                         if(ListRead[j].ListRead[kj]!=0)
                            fprintf(stream2s, "%d\n",ListRead[j].ListRead[kj]);
                      }
                      fprintf(stream2s, ".\n");
                   }
                }
                fprintf(stream2s, ".\n");
                fclose(stream2s);
                stream2s=fopen("news.rc", "w");
                fprintf(stream2s, "%s\n", hostname);
                fprintf(stream2s, "%s\n", mailserver);
                fprintf(stream2s,"%s\n",email);
                fprintf(stream2s,"%s\n", realn);
                fprintf(stream2s,"%s\n",organ);
                fprintf(stream2s,"%d\n",TGroup);
                fprintf(stream2s, "%d\n", SortOrd);
                fprintf(stream2s, "%d\n", FastLoad);
                fprintf(stream2s, "%s\n", DownloadDir);
                fprintf(stream2s, "%d\n", UUDownBeep);
                fprintf(stream2s,"%s\n",RegName);
                fprintf(stream2s,"%d\n",Key);
                fprintf(stream2s, "%d\n", Code);
                fclose(stream2s);
                }
                DosDelete("article.txt");
                DosDelete("post.txt");
                DosDelete("sort.txt");
                DosDelete("header.txt");
                DosDelete("head.txt");
                DosDelete("file.uue");
                DosDelete("uu.tmp");
                DosDelete("mail.txt");
                WinPostMsg(hwnd, WM_QUIT, 0,0);}
        break;
        default:
                MsgProcess = FALSE;
        }
        return (MsgProcess ? ((MRESULT) 0L):WinDefWindowProc(hwnd, msg, parm1, parm2));
}

MRESULT EXPENTRY Setting_Func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
switch(msg)
   {
   case WM_COMMAND:
        switch (SHORT1FROMMP(parm1))
           {
           case SET_OK:
              WinQueryDlgItemText(hwnd, SET_NEWSF, 1000,hostname);
              WinQueryDlgItemText(hwnd, SET_MAILSF, 1000,mailserver);
              WinQueryDlgItemText(hwnd, SET_EMAILF, 1000,email);
              WinQueryDlgItemText(hwnd, SET_NAMEF, 1000, realn);
              WinQueryDlgItemText(hwnd, SET_ORGF, 1000, organ);
              i=strlen(realn);
              realn[i]='\0';
              stream2s=fopen("news.rc", "w");
              fprintf(stream2s, "%s\n", hostname);
              fprintf(stream2s, "%s\n", mailserver);
              fprintf(stream2s,"%s\n",email);
              fprintf(stream2s,"%s\n", realn);
              fprintf(stream2s,"%s\n",organ);
              fprintf(stream2s,"%d\n",TGroup);
              fprintf(stream2s, "%d\n", SortOrd);
              fprintf(stream2s, "%d\n", FastLoad);
              fprintf(stream2s, "%s\n", DownloadDir);
              fprintf(stream2s, "%d\n", UUDownBeep);
              fclose(stream2s);
              WinDismissDlg(hwnd, SETTING);
              return (MRESULT)TRUE;
           }
      default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
   }
return (MRESULT)0;
}
MRESULT EXPENTRY Login_Func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
   char UserName[30];
   char Password[30];
   char tmpPass[30];
   int UsC, crypt;
   switch(msg)
   {
      case WM_COMMAND:
        switch (SHORT1FROMMP(parm1))
        {
           case LOG_OK:
             for(UsC=0;UsC<30;UsC++)
             {
             UserName[UsC]='\0';
             Password[UsC]='\0';
             tmpPass[UsC]='\0';
             }
             WinQueryDlgItemText(hwnd, LOG_NAMEF, 30,UserName);
             WinQueryDlgItemText(hwnd, LOG_PASSF, 30,Password);
             for(UsC=0;UsC<UserCount;UsC++)
             {
                if(strcmp(Users[UsC].UName, UserName)==0)
                {
                   for(crypt=0;crypt<strlen(Password);crypt++)
                   {
                      if(crypt%2)
                         tmpPass[crypt]=Password[strlen(Password)-crypt]-1;
                      else
                         tmpPass[crypt]=Password[crypt]+1;
                   }
                   if(strcmp(Users[UsC].Pass,tmpPass)==0)
                   {
                       LoginFailed=FALSE;
                       strcpy(CurrentU.UName,Users[UsC].UName);
                       strcpy(CurrentU.Pass,Users[UsC].Pass);
                       strcpy(CurrentU.Dir, Users[UsC].Dir);
                       WinDismissDlg(hwnd, LOGIN);
                       return (MRESULT)TRUE;
                   }
                }
             }
             try++;
             if(try==3)
             {
               LoginFailed=TRUE;
               WinDismissDlg(hwnd, LOGIN);
             }
             return (MRESULT)TRUE;
        }
       default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
   }
return (MRESULT)0;
}

MRESULT EXPENTRY VHeader(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
  FILE *stream23;
  int     b1,il1,il2;
  char    *filettu;
  char    tstring4[MAXLINE];

  switch(msg)
  {
     case WM_INITDLG:
        WinSetDlgItemText(hwnd, VH_HEADER, "");
        stream23=fopen("head.txt", "r");
        if (stream23)
        {
           while(filettu!=NULL)
           {
              filettu=fgets(tstring4, 256, stream23);
              il1=strcspn(tstring4, "\0");
              tstring4[il1]='\r';
              tstring4[il1+1]='\0';
              WinSendDlgItemMsg(hwnd, VH_HEADER,MLM_SETIMPORTEXPORT, (MPARAM)tstring4, (MPARAM)strlen(tstring4));
              WinSendDlgItemMsg(hwnd, VH_HEADER,MLM_IMPORT, (MPARAM)&ipt, MPFROMLONG(strlen(tstring4)));
           }
       fclose(stream23);
       }
     break;          /*
     case WM_COMMAND:
        switch (SHORT1FROMMP(parm1))
      {
       return (MRESULT)TRUE;
      }                */
      default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
  }
  return (MRESULT)0;
}


MRESULT EXPENTRY Subscribe_Func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
switch(msg)
{
   case WM_INITDLG:
      WinSendDlgItemMsg(hwnd, SGTEXTF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
   break;
   case WM_COMMAND:
      switch (SHORT1FROMMP(parm1))
      {
         case SG_OK:
            WinQueryDlgItemText(hwnd, SGTEXTF, 1000,SGroup);
            WinDismissDlg(hwnd, SGROUP);
         return (MRESULT)TRUE;
      }
      default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
}
return (MRESULT)0;
}


MRESULT EXPENTRY MSearch(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
        switch(msg)
        {
        case WM_INITDLG:
                WinSendDlgItemMsg(hwnd, FMTEXTF, EM_SETTEXTLIMIT, MPFROMSHORT(256),0);
        break;
        case WM_COMMAND:
                switch(SHORT1FROMMP(parm1))
                {
                case FM_UUDECODE:
                   if(0!=WinSendMsg(hwndLB, LM_QUERYITEMCOUNT, 0,0))
                   {
                        item=WinQueryLboxSelectedItem(hwndLB);
                        WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                        articlei[0]='*';
                        WinSendMsg(hwndLB, LM_SETITEMTEXT,  MPFROM2SHORT(item,180), MPFROMP(articlei));
                        WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(item),(MPARAM)FALSE);
                        Drop(articlei, articlei,1);
                        sscanf(articlei, "%d", &mki2);
                        mki=0;
                        while(NULL==strstr(ListRead[mki].Groupname,groupname))
                            mki++;
                        NotThere=FALSE;
                        for(mki3=0;mki3<ListRead[mki].Count;mki3++)
                        {
                            if(mki2==ListRead[mki].ListRead[mki3])
                            {
                                NotThere=TRUE;
                                break;
                            }
                        }
                        if(!NotThere)
                        {
                            ListRead[mki].ListRead[ListRead[mki].Count]=mki2;
                            ListRead[mki].Count++;
                            mki4=mki;
                            mki=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(groupname));
                            WinSendMsg(hwndLB2, LM_QUERYITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                            sscanf(tmpstr4, "%d", &mki2);
                            mki2--;
                            if(mki2<=0)
                            {
                                Large=0;
                                for(mki3=0;mki3<ListRead[mki4].Count;mki3++)
                                {
                                   if(Large<ListRead[mki4].ListRead[mki3])
                                         Large=ListRead[mki4].ListRead[mki3];
                                }
                                ListRead[mki4].ListRead[ListRead[mki4].Count]=abs(ListRead[mki4].ListRead[0]);
                                ListRead[mki4].ListRead[0]=Large*(-1);
                                ListRead[mki4].Count++;
                                mki2=0;
                            }
                            sprintf(tmpstr4, "%d",mki2);
                            while(strlen(tmpstr4)<5)
                              strcat(tmpstr4, " ");
                            strcat(tmpstr4, groupname);
                            strcat(tmpstr4, " ");
                            WinSendMsg(hwndLB2, LM_SETITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                        }
                        item=(int)WinSendMsg(hwndLBUUQueue, LM_SEARCHSTRING, MPFROM2SHORT(LSS_CASESENSITIVE,LIT_FIRST),MPFROMP(articlei));
                        if (item==LIT_NONE)
                        {
                            qc++;
                            if (qc==1000)
                              qc=0;
                            WinSendMsg(hwndLBUUQueue, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(articlei));
                            i=strcspn(articlei, " ");
                            for(a=0;a<i;a++)
                               UUNames[qc].MID[a]=articlei[a];
                            strcpy(UUNames[qc].Group, groupname);
                            UUNames[qc].MID[i]='\0';
                        }
                        WinSetWindowText(hwndStatTxtUU, "Queuing article.");
                        if(!Decoding)
                           _beginthread(UUDecodePrep,NULL, 32768, (void *)hwnd);
                        if(Connected)
                        Changed();
                   }
                return (MRESULT)TRUE;
                case FM_FIND:
                       WinQueryDlgItemText(hwnd, FMTEXTF, 1000,SGroup);
                       SGItem=(int)WinSendMsg(hwndLB, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING, LIT_FIRST),MPFROMP(SGroup));
                       if(SGItem!=LIT_NONE)
                       {
                            WinSendMsg(hwndLB, LM_SETTOPINDEX, MPFROMP(SGItem),0);
                            WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(SGItem), (MPARAM)TRUE);
                       }
                return (MRESULT)TRUE;
                case FM_NEXT:
                      WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(SGItem),(MPARAM)FALSE);
                      SGItem=(int)WinSendMsg(hwndLB, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING, SGItem),MPFROMP(SGroup));
                      if(SGItem!=LIT_NONE)
                      {
                           WinSendMsg(hwndLB, LM_SETTOPINDEX, MPFROMP(SGItem),0);
                           WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(SGItem), (MPARAM)TRUE);
                      }
                return (MRESULT)TRUE;
                case FM_OPEN:
                        WinSetWindowText(hwndStatTxt, "Loading article.");
                        item=WinQueryLboxSelectedItem(hwndLB);
                        WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                        Change=TRUE;
                        item=WinQueryLboxSelectedItem(hwndLB);
                        WinSendMsg(hwndLB, LM_QUERYITEMTEXT, MPFROM2SHORT(item,180), MPFROMP(articlei));
                        articlei[0]='*';
                        WinSendMsg(hwndLB, LM_SETITEMTEXT,  MPFROM2SHORT(item,180), MPFROMP(articlei));
                        WinSendMsg(hwndLB, LM_SELECTITEM, MPFROMP(item),(MPARAM)FALSE);
                        Drop(articlei, articlei, 1);
                        sscanf(articlei, "%d", &mki2);
                        mki=0;
                        while(NULL==strstr(ListRead[mki].Groupname,groupname))
                        {
                           mki++;
                        }
                        NotThere=FALSE;
                        for(mki3=0;mki3<ListRead[mki].Count;mki3++)
                        {
                             if(mki2==ListRead[mki].ListRead[mki3])
                             {
                                 NotThere=TRUE;
                                 break;
                             }
                        }
                        if(!NotThere)
                        {
                             ListRead[mki].ListRead[ListRead[mki].Count]=mki2;
                             ListRead[mki].Count++;
                             mki=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(groupname));
                             WinSendMsg(hwndLB2, LM_QUERYITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                             sscanf(tmpstr4, "%d", &mki2);
                             mki2--;
                             sprintf(tmpstr4, "%d",mki2);
                             while(strlen(tmpstr4)<5)
                                strcat(tmpstr4, " ");
                             strcat(tmpstr4, groupname);
                             strcat(tmpstr4, " ");
                             WinSendMsg(hwndLB2, LM_SETITEMTEXT,  MPFROM2SHORT(mki,180), MPFROMP(tmpstr4));
                        }
                        i=strcspn(articlei, " ");
                        for(a=0;a<i;a++)
                           article[a]=articlei[a];
                        article[i]='\0';
                        _beginthread(GetArticle,NULL, 32768, (void *)hwnd);
                        Changed();
                        WinSetWindowText(hwndStatTxt, "Retrieving Article");
                return (MRESULT)TRUE;
                case FM_CANCEL:
                   WinDismissDlg(hwnd, FMESSAGE);
                return (MRESULT)TRUE;
                }
                  default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
        }
return (MRESULT)0;
}
MRESULT EXPENTRY Search_Func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
switch(msg)
{
   case WM_INITDLG:
      WinSendDlgItemMsg(hwnd, FGTEXTF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
   break;
   case WM_COMMAND:
   switch (SHORT1FROMMP(parm1))
   {
        case FG_OK:
        case FG_CANCEL:
            WinDismissDlg(hwnd, FGROUP);
        return (MRESULT)TRUE;
      case FG_FIND:
         WinQueryDlgItemText(hwnd, FGTEXTF, 1000,SGroup);
         SGItem=(int)WinSendMsg(hwndLBALL, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING, LIT_FIRST),MPFROMP(SGroup));
         if(SGItem!=LIT_NONE)
         {
             WinSendMsg(hwndLBALL, LM_SETTOPINDEX, MPFROMP(SGItem),0);
             WinSendMsg(hwndLBALL, LM_SELECTITEM, MPFROMP(SGItem), (MPARAM)TRUE);
         }
         return (MRESULT)TRUE;
      case FG_NEXT:
         SGItem=(int)WinSendMsg(hwndLBALL, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING, SGItem),MPFROMP(SGroup));
         if(SGItem!=LIT_NONE)
         {
             WinSendMsg(hwndLBALL, LM_SETTOPINDEX, MPFROMP(SGItem),0);
             WinSendMsg(hwndLBALL, LM_SELECTITEM, MPFROMP(SGItem), (MPARAM)TRUE);
         }
      return (MRESULT)TRUE;
      case FG_SUBSCRIBE:
        SGItem=WinQueryLboxSelectedItem(hwndLBALL);
        WinSendMsg(hwndLBALL, LM_QUERYITEMTEXT, MPFROM2SHORT(SGItem,180), MPFROMP(groupname));
        _beginthread(Subscribe, NULL, 32768, (void *)hwnd);
      return (MRESULT)TRUE;
   }
   default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
}
return (MRESULT)0;
}

MRESULT EXPENTRY Edit_Func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
FILE *userf;
int UsC,yn;
switch(msg)
{
   case WM_INITDLG:
      for(UsC=0;UsC<UserCount;UsC++)
      {
        yn=(int)WinSendDlgItemMsg(hwnd, UE_LBNAME,LM_SEARCHSTRING, MPFROM2SHORT(LSS_CASESENSITIVE, LIT_FIRST), MPFROMP(Users[UsC].UName));
        if(yn==LIT_NONE)
        WinSendDlgItemMsg(hwnd, UE_LBNAME, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(Users[UsC].UName));
      }
   break;
   case WM_COMMAND:
   switch (SHORT1FROMMP(parm1))
   {
      case UE_OK:
         WinDismissDlg(hwnd, USEREDIT);
      return (MRESULT) TRUE;
      case UE_ADD:
         WinDlgBox(HWND_DESKTOP,hwnd,AUser_Func,0,ADDUSER,0);
         userf=fopen("user.lst", "w");
         for(UsC=0;UsC<UserCount;UsC++)
         {
            if(Users[UsC].UName[0]!='\0')
               fprintf(userf, "%s %s %s\n",Users[UsC].UName,Users[UsC].Pass,Users[UsC].Dir);
            yn=(int)WinSendDlgItemMsg(hwnd, UE_LBNAME,LM_SEARCHSTRING, MPFROM2SHORT(LSS_CASESENSITIVE, LIT_FIRST), MPFROMP(Users[UsC].UName));
            if(yn==LIT_NONE)
               WinSendDlgItemMsg(hwnd, UE_LBNAME, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(Users[UsC].UName));
               DosCreateDir(Users[UsC].Dir,0);
         }
         fclose(userf);
      return (MRESULT) TRUE;
   }
default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
}
return (MRESULT)0;
}
MRESULT EXPENTRY AUser_Func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
char UserName[30];
char Password[30];
char Password2[30];
char Directory[30];
int  crypt,UsC,yn;
switch(msg)
{
   case WM_COMMAND:
      switch (SHORT1FROMMP(parm1))
         {
         case AU_OK:
         WinQueryDlgItemText(hwnd, AU_NAMEF, 1000, UserName);
         WinQueryDlgItemText(hwnd, AU_PASSF, 1000, Password);
         WinQueryDlgItemText(hwnd, AU_PVERF, 1000, Password2);
         WinQueryDlgItemText(hwnd, AU_DIRF, 1000, Directory);
         if(0!=strcmp(Password, Password2))
         {
                WinMessageBox(HWND_DESKTOP, hwnd, "Passwords do not match.","Password Error", 0, MB_OK|MB_ERROR);
         }
         else
         {
                strcpy(Users[UserCount].UName,UserName);
                for(crypt=0;crypt<strlen(Password);crypt++)
                {
                        if(crypt%2)
                          Users[UserCount].Pass[crypt]=Password[strlen(Password)-crypt]-1;
                        else
                          Users[UserCount].Pass[crypt]=Password[crypt]+1;
                }
                strcpy(Users[UserCount].Dir, Directory);
                UserCount++;
         WinDismissDlg(hwnd, ADDUSER);
         WinPostMsg(hwnd, WM_UPDATEUL, 0,0);
         }
         return (MRESULT)TRUE;
         }
        default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
        }
      return (MRESULT)0;
}

MRESULT EXPENTRY SNotebook(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
   HWND hwndFrame;

   switch(msg)
   {
      case WM_INITDLG:
      {
        WinSetWindowULong(hwnd, QWL_USER, (ULONG)parm2);
        InsertPage(hwnd);
        break;
      }
      case WM_CONTROL:
        if (ControlMsg(hwnd,SHORT1FROMMP(parm1), SHORT2FROMMP(parm1), parm2))
        {
                return 0;
        }
        else
                break;
      case WM_SYSCOMMAND:
      {
        if(SHORT1FROMMP(parm1)==SC_CLOSE)
        {       ULONG SaveSet;
                INT iCount;
                SaveSet=WinMessageBox(HWND_DESKTOP, hwnd,
                "Do you wish to save changes?",
                "Save Settings?", 0, MB_YESNO|MB_QUERY);
                if (SaveSet==MBID_YES)
                {
                   for(iCount=0;iCount<PAGE_COUNT;iCount++)
                        if(nbpage[iCount].hwnd!=NULLHANDLE)
                                WinSendMsg(nbpage[iCount].hwnd, WM_SAVESETTINGS,(MPARAM)0,(MPARAM)0);
                }

        }
        else
           break;
     }
   }
   return WinDefDlgProc(hwnd, msg, parm1, parm2);
}

BOOL InsertPage(HWND hwnd)
{
        int iCount;
        WinSendDlgItemMsg(hwnd, SN_ONE, BKM_SETNOTEBOOKCOLORS, MPFROMLONG(SYSCLR_FIELDBACKGROUND), MPFROMSHORT(BKA_BACKGROUNDPAGECOLORINDEX));
        SetTabDimensions(WinWindowFromID(hwnd, SN_ONE));
        for(iCount=0;iCount<PAGE_COUNT;iCount++)
           SetUpPage(hwnd, &nbpage[iCount], iCount);
        return TRUE;
}

static BOOL ControlMsg(HWND hwnd, USHORT usControl, USHORT usEvent, MPARAM parm2)
{
    BOOL fProcessed=FALSE;
    HWND hwndDlg1;
    switch(usControl)
    {
       case SN_ONE:
          switch(usEvent)
          {
              case BKN_PAGESELECTED:
                 SetNBPage(hwnd, (PPAGESELECTNOTIFY) parm2);
                 fProcessed=TRUE;
              break;
           }
           break;
     }
     return fProcessed;
}

static VOID SetNBPage(HWND hwnd, PPAGESELECTNOTIFY ppsn)
{
      HWND hwndDlg;
      PNBPAGE pnbp=(PNBPAGE)WinSendMsg(ppsn->hwndBook, BKM_QUERYPAGEDATA,MPFROMLONG( ppsn->ulPageIdNew ), NULL );
      if(!pnbp)
          return;
      else if(pnbp==(PNBPAGE) BOOKERR_INVALID_PARAMETERS)
          return;
      if(pnbp->fParent)
      {
          ULONG ulPageFwd, ulPageNew;
          ulPageFwd=(ULONG)WinSendMsg(ppsn->hwndBook, BKM_QUERYPAGEID, MPFROMLONG(ppsn->ulPageIdNew), MPFROM2SHORT(BKA_PREV, BKA_MAJOR));
          if(ulPageFwd==ppsn->ulPageIdCur)
                ulPageNew=(ULONG)WinSendMsg(ppsn->hwndBook, BKM_QUERYPAGEID, MPFROMLONG(ppsn->ulPageIdNew), MPFROM2SHORT(BKA_PREV, BKA_MAJOR));
          else
                ulPageNew=ulPageFwd;
      }
      else
      {
          hwndDlg=(HWND)WinSendMsg(ppsn->hwndBook, BKM_QUERYPAGEWINDOWHWND, MPFROMLONG(ppsn->ulPageIdNew), NULL);
          if(hwndDlg==(HWND)BOOKERR_INVALID_PARAMETERS)
                hwndDlg=NULLHANDLE;
          else if( !hwndDlg )
                hwndDlg = LoadAndAssociate( hwnd, pnbp, ppsn );
      }
      return;
}

static HWND LoadAndAssociate(HWND hwndClient, PNBPAGE pnbp, PPAGESELECTNOTIFY ppsn)
{
     HWND hwndDlg = WinLoadDlg( hwndClient, hwndClient, pnbp->pfnwpDlg, 0,pnbp->idDlg, pnbp );
     if  (hwndDlg)
     {

          if( !WinSendMsg( ppsn->hwndBook, BKM_SETPAGEWINDOWHWND,MPFROMP( ppsn->ulPageIdNew ),MPFROMLONG(hwndDlg)))
          {
              WinDestroyWindow( hwndDlg );
              hwndDlg = NULLHANDLE;
          }
          else
              iPagesLoaded++;
     }
     return hwndDlg;
}
BOOL InitializeNoteBook(HWND hwnd)
{
    HWND hwndPage;
    ULONG ulPageId;
    APIRET  dlgret;
    PDLGTEMPLATE pDlgt;
    ulPageId = (LONG)WinSendDlgItemMsg(hwnd,SN_ONE,BKM_INSERTPAGE, NULL,
               MPFROM2SHORT((BKA_STATUSTEXTON | BKA_AUTOPAGESIZE | BKA_MAJOR),BKA_LAST));
    if(!ulPageId)
      return FALSE;
    if(!WinSendDlgItemMsg(hwnd, SN_ONE,BKM_SETSTATUSLINETEXT, MPFROMLONG(ulPageId),MPFROMP("Page 1 of 4")))
      return FALSE;
    if(!WinSendDlgItemMsg(hwnd, SN_ONE,BKM_SETTABTEXT, MPFROMLONG(ulPageId),  MPFROMP("Network")))
      return FALSE;
//    DosAllocMem((PPVOID)&pDlgt, sizeof(DLGTEMPLATE), PAG_COMMIT|PAG_READ|PAG_WRITE);
//    dlgret=DosGetResource((HMODULE)0, RT_DIALOG, ID_NBPAGE1, (PPVOID)&pDlgt);
    hwndPage=WinCreateDlg(HWND_DESKTOP, hwnd, SNotebook, pDlgt, NULL);
    if(!hwndPage)
      return FALSE;
//    DosFreeMem(pDlgt);
    if(!WinSendDlgItemMsg(hwnd, SN_ONE, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageId), MPFROMHWND(hwndPage)))
      return FALSE;
   return TRUE;
}
MRESULT EXPENTRY App_Func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
   switch(msg)
   {
   case WM_COMMAND:
      switch (SHORT1FROMMP(parm1))
      {

             case AP_WO:
                APPEND=0;
                WinDismissDlg(hwnd, APPENDDLG);
             break;
             case AP_AP:
                APPEND=1;
                WinDismissDlg(hwnd, APPENDDLG);
             break;
             case AP_CA:
                APPEND=2;
             WinDismissDlg(hwnd, APPENDDLG);
             return (MRESULT)TRUE;
      }
      default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
   }
   return (MRESULT)0;
}

MRESULT EXPENTRY ab_func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
switch(msg){
case WM_COMMAND:
        switch (SHORT1FROMMP(parm1)) {
                case DLG1INFO:
                WinSetWindowPos(hwnd,HWND_TOP,200,100,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                WinDlgBox(HWND_DESKTOP, hwnd, reg_func, 0, DLG2, 0);
                break;
                case DLG1EXIT:
                        WinDismissDlg(hwnd, DLG1EXIT);
                        return (MRESULT)TRUE;
                }
                default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
                }
                return (MRESULT)0;
}
MRESULT EXPENTRY AKillFile(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
   int KItem,KCount;
   char KString[MAXLINE];
   FILE *KFile;
   switch(msg)
   {
      case WM_INITDLG:
        WinSendDlgItemMsg(hwnd, KTEXTF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
        KItem=0;
        while(0!=strncmp(article, Head[KItem].Mid,i))
            KItem++;
       WinSetDlgItemText(hwnd, KTEXTF, Head[KItem].From);
      break;
      case WM_COMMAND:
      switch (SHORT1FROMMP(parm1))
      {
         case KOK:
            WinQueryDlgItemText(hwnd, KTEXTF, 256, KString);
            KItem=(int)WinSendMsg(hwndLBKill, LM_SEARCHSTRING, MPFROM2SHORT(LSS_CASESENSITIVE,LIT_FIRST),MPFROMP(KString));
            if(KItem==LIT_NONE)
            {
               WinSendMsg(hwndLBKill, LM_INSERTITEM, MPFROMSHORT(0),KString);
            }
            KItem=(int)WinSendMsg(hwndLBKill, LM_QUERYITEMCOUNT, 0,0);
            KFile=fopen("newsbeat.kil", "w");
            if(KFile)
            {
               for(KCount=0;KCount<KItem;KCount++)
               {
                  WinSendMsg(hwndLBKill, LM_QUERYITEMTEXT, MPFROM2SHORT(KCount,256), MPFROMP(KString));
                  fprintf(KFile,"%s\n",KString);
               }
               fprintf(KFile, ".\n");
            fclose(KFile);
            }
            WinDismissDlg(hwnd, AKILL);
         break;
         case KCANCEL:
             WinDismissDlg(hwnd, AKILL);
         return (MRESULT)TRUE;
      }
      default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
      }
      return (MRESULT)0;
}


MRESULT EXPENTRY reg_func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
switch(msg){
case WM_COMMAND:
        switch (SHORT1FROMMP(parm1)) {
                case REGISTER:
                        WinSetWindowPos(hwnd,HWND_TOP,200,100,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
                        Tries=0;
                        WinDlgBox(HWND_DESKTOP, hwnd, Register, 0, RegWindow, 0);
                        break;
                case DLG2EXIT:
                        WinDismissDlg(hwnd, DLG1EXIT);
                        return (MRESULT)TRUE;
                }
                default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
                }
                return (MRESULT)0;
        }
MRESULT EXPENTRY Register(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
   char TMPFR[MAXLINE];
   switch(msg)
   {
      case WM_INITDLG:
         WinSendDlgItemMsg(hwnd, REGNAMEF, EM_SETTEXTLIMIT,MPFROMSHORT(200),0);
         WinSendDlgItemMsg(hwnd, REGKEYF, EM_SETTEXTLIMIT,MPFROMSHORT(200),0);
         WinSendDlgItemMsg(hwnd, REGCODEF, EM_SETTEXTLIMIT,MPFROMSHORT(200),0);
         WinSetDlgItemText(hwnd, REGNAMEF, RegName);
         sprintf(TMPFR, "%d", Key);
         WinSetDlgItemText(hwnd, REGKEYF, TMPFR);
         sprintf(TMPFR, "%d", Code);
         WinSetDlgItemText(hwnd, REGCODEF, TMPFR);
      break;
      case WM_COMMAND:
      switch (SHORT1FROMMP(parm1))
      {
         case PB_REGBUT:
            WinQueryDlgItemText(hwnd, REGNAMEF, MAXLINE,RegName);
            WinQueryDlgItemText(hwnd, REGKEYF, MAXLINE, TMPFR);
            sscanf(TMPFR, "%d", &Key);
            WinQueryDlgItemText(hwnd, REGCODEF, MAXLINE, TMPFR);
            sscanf(TMPFR, "%d", &Code);
            if (strlen(RegName)>1)
            {
               if (Encrypt(RegName, Key, Code))
               {
                  Registered=TRUE;
                  WinMessageBox(HWND_DESKTOP, hwnd, "Thank you for buying Newsbeat.","Registration Complete.", 0, MB_OK|MB_INFORMATION);
                  stream2s=fopen("news.rc", "w");
                  fprintf(stream2s, "%s\n", hostname);
                  fprintf(stream2s, "%s\n", mailserver);
                  fprintf(stream2s,"%s\n",email);
                  fprintf(stream2s,"%s\n", realn);
                  fprintf(stream2s,"%s\n",organ);
                  fprintf(stream2s,"%d\n",TGroup);
                  fprintf(stream2s, "%d\n", SortOrd);
                  fprintf(stream2s, "%d\n", FastLoad);
                  fprintf(stream2s, "%s\n", DownloadDir);
                  fprintf(stream2s, "%d\n", UUDownBeep);
                  fprintf(stream2s,"%s\n",RegName);
                  fprintf(stream2s,"%d\n",Key);
                  fprintf(stream2s, "%d\n", Code);
                  fclose(stream2s);
                  WinDismissDlg(hwnd, RegWindow);
               }
               else
               {
                  Registered=FALSE;
                  WinMessageBox(HWND_DESKTOP, hwnd, "Registration Information Incorrect.","Incomplete.", 0, MB_OK|MB_WARNING);
                  Tries++;
                  if (Tries>3)
                       WinDismissDlg(hwnd, RegWindow);
               }
            }
            return (MRESULT) TRUE;
            case PB_CANCELREG:
                    WinDismissDlg(hwnd, PB_CANCELREG);
                            return (MRESULT)TRUE;
        }
        default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
   }
            return (MRESULT)0;
}



MRESULT EXPENTRY editor_func(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
FILE *out1, *in1,*stream23,*stream24;
FILEDLG fd1;
HWND    fdlg1;
int     b1,il1,il2;
char    fd1Title[]="Attach File";
char    *filettu,UUFilename[MAXLINE];
char    tstring4[MAXLINE],tstring23[MAXLINE];
switch(msg){
case WM_INITDLG:
        WinLoadMenu(hwnd, 0, EDITORM);
        WinSendMsg(hwnd, WM_UPDATEFRAME, (MPARAM)FID_MENU, 0);
        WinSendDlgItemMsg(hwnd, EDI_MAILMSG, BM_SETCHECK,MPFROMP(TRUE),0);
        WinSendDlgItemMsg(hwnd, EDI_POSTMSG, BM_SETCHECK,MPFROMP(TRUE), 0);
        WinSendDlgItemMsg(hwnd, EDI_WORLD, BM_SETCHECK,MPFROMP(TRUE), 0);
        WinSendDlgItemMsg(hwnd, EDI_FROMF, EM_SETTEXTLIMIT,MPFROMSHORT(200),0);
        WinSendDlgItemMsg(hwnd, EDI_SUBF, EM_SETTEXTLIMIT,MPFROMSHORT(200),0);
        WinSendDlgItemMsg(hwnd, EDI_DISF, EM_SETTEXTLIMIT,MPFROMSHORT(200),0);
        WinSendDlgItemMsg(hwnd, EDI_TOF, EM_SETTEXTLIMIT,MPFROMSHORT(200),0);
        WinSetDlgItemText(hwnd, EDI_DISF, groupname);
        if (New)
          WinSetDlgItemText(hwnd, EDI_MSGF, "");
        else
        {
        item=0;
        while(0!=strncmp(article, Head[item].Mid,i))
             item++;
        Drop(Head[item].Subject, Head[item].Subject,1);
        WinSetDlgItemText(hwnd, EDI_SUBF, Head[item].Subject);
        WinSetDlgItemText(hwnd, EDI_TOF, Head[item].From);
        sprintf(tstring4, "%s wrote:\n\n",Head[item].From);
        WinSetDlgItemText(hwnd, EDI_MSGF, tstring4);
        stream23=fopen("article.txt", "r");
        if (stream23)
        {
           while(filettu!=NULL)
           {
               filettu=fgets(tstring4, 256, stream23);
               il1=strcspn(tstring4, "\0");
               tstring4[il1]='\r';
               tstring4[il1+1]='\0';
               strcpy(tstring23, ">");
               strcat(tstring23,tstring4);
               WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_SETIMPORTEXPORT, (MPARAM)tstring23, (MPARAM)strlen(tstring23));
               WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_IMPORT, (MPARAM)&ipt, MPFROMLONG(strlen(tstring23)));
            }
            fclose(stream23);
         }
        }
        filettu=(char *)1;
        WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_SETIMPORTEXPORT, (MPARAM)"\r\n\r\0", (MPARAM)strlen("\r\n\r\0"));
        WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_IMPORT, (MPARAM)&ipt, MPFROMLONG(strlen("\r\n\r\0")));
        WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_SETIMPORTEXPORT, (MPARAM)"\r\n\r\0", (MPARAM)strlen("\r\n\r\0"));
        WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_IMPORT, (MPARAM)&ipt, MPFROMLONG(strlen("\r\n\r\0")));
        stream23=fopen("newsbeat.sig", "r");
        if (stream23)
        {
           while(filettu!=NULL)
           {
              filettu=fgets(tstring4, 256, stream23);
              il1=strcspn(tstring4, "\0");
              tstring4[il1]='\r';
              tstring4[il1+1]='\0';
              WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_SETIMPORTEXPORT, (MPARAM)tstring4, (MPARAM)strlen(tstring4));
              WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_IMPORT, (MPARAM)&ipt, MPFROMLONG(strlen(tstring4)));
           }
        fclose(stream23);
        }
        sprintf(tstring, "%s (%s)", email, realn);
        WinSetDlgItemText(hwnd, EDI_FROMF, tstring);
break;
case WM_COMMAND:
        switch (SHORT1FROMMP(parm1)) {
                case EDI_CANCEL:
                case EFABORT:
                WinDismissDlg(hwnd, EDITOR);
                break;
                case EFSEND:
                case EDI_OK:
                   WinQueryDlgItemText(hwnd, EDI_FROMF, 1000, PFrom);
                   WinQueryDlgItemText(hwnd, EDI_SUBF, 1000, PSubject);
                   WinQueryDlgItemText(hwnd, EDI_DISF, 1000, PDistribution);
                   WinQueryDlgItemText(hwnd, EDI_TOF, 1000, EMailTo);
                   lOffset=0;
                   if(WinQueryButtonCheckstate(hwnd, EDI_POSTMSG))
                   {
                        PostTF=TRUE;
                        while(strlen(PDistribution)!=strcspn(PDistribution, " "))
                        {
                            for(i=strcspn(PDistribution, " ");i<strlen(PDistribution);i++)
                               PDistribution[i]=PDistribution[i+1];
                        }
                      //  RndID=time(NULL);
                        stream23=fopen("post.txt", "w");
                        fprintf(stream23, "Path: %s\r\n",organ);
                        fprintf(stream23, "From: %s (%s)\r\n",email,realn);
                        fprintf(stream23, "Newsgroups: %s\r\n",PDistribution);
                        fprintf(stream23, "Subject: %s\r\n", PSubject);
                      //fprintf(stream23, "Message-ID: <%i@%s>\n", RndID, hostname);
                        if(WinQueryButtonCheckstate(hwnd, EDI_WORLD))
                           fprintf(stream23, "Distribution: world\r\n");
                        else
                           fprintf(stream23, "Distribution: local\r\n");
                        fprintf(stream23, "X-Newsreader: NewsBeat For Os/2 %s", Vers);
                        if(!Registered)
                            fprintf(stream23, " - Unregistered");
                            fprintf(stream23, "\r\n", Vers);

                        fputs("\r\n\r\n", stream23);
                   }
                   if(WinQueryButtonCheckstate(hwnd, EDI_MAILMSG))
                   {
                           MailTF=TRUE;
                           stream24=fopen("mail.txt", "w");
                           fprintf(stream24, "From: %s (%s)\n",email,realn);
                           fprintf(stream24, "To: %s\n", EMailTo);
                           fprintf(stream24, "Subject: %s\n", PSubject);
                           fprintf(stream24, "X-Newsreader: NewsBeat For Os/2 %s", Vers);
                           if(!Registered)
                               fprintf(stream24, " - Unregistered");
                           fprintf(stream24, "\n", Vers);

                           fputs("\n\n", stream24);
                   }
                   memset(szMleBuf, 0, sizeof(szMleBuf));
                   WinSendDlgItemMsg(hwnd, EDI_MSGF, MLM_SETIMPORTEXPORT, MPFROMP(szMleBuf), MPFROMSHORT((USHORT)sizeof(szMleBuf)));
                        cbCopy=(ULONG)WinSendDlgItemMsg(hwnd, EDI_MSGF, MLM_QUERYFORMATTEXTLENGTH, MPFROMLONG(lOffset), MPFROMLONG((-1)));
                        while(cbCopy!=0)
                        {
                           WinSendDlgItemMsg(hwnd, EDI_MSGF, MLM_EXPORT, MPFROMP(&lOffset), MPFROMP(&cbCopy));
                           if(PostTF)
                           fputs(szMleBuf,stream23);
                           if(MailTF)
                           fputs(szMleBuf,stream24);
                           for(i=0;i<sizeof(szMleBuf);i++)
                             szMleBuf[i]='\0';
                        }


                   WinDismissDlg(hwnd, EDITOR);
                   if (PostTF)
                   {
                      fputs("\r\n.\r\n",stream23);
                      fclose(stream23);
                      _beginthread(Post,NULL, 32768, (void *)hwnd);
                      PostTF=FALSE;
                   }
                   if (MailTF)
                   {
                      fputs("\n.\n",stream24);
                      fclose(stream24);
                      _beginthread(Mail,NULL, 32768, (void *)hwnd);
                      MailTF=FALSE;
                    }
                break;
                case EFCOPY:
                case EDI_COPY:
                   WinSendDlgItemMsg(hwnd, EDI_MSGF, MLM_COPY,0,0);
                return (MRESULT) TRUE;
                case EFPASTE:
                case EDI_PASTE:
                   WinSendDlgItemMsg(hwnd, EDI_MSGF, MLM_PASTE,0,0);
                return (MRESULT) TRUE;
                case EFCUT:
                case EDI_CUT:
                   WinSendDlgItemMsg(hwnd, EDI_MSGF, MLM_CUT,0,0);
                return (MRESULT) TRUE;
                case EFUNDO:
                   WinSendDlgItemMsg(hwnd, EDI_MSGF, MLM_UNDO,0,0);
                return (MRESULT) TRUE;
                case EFCLEAR:
                case EDI_CLEAR:
                   WinSendDlgItemMsg(hwnd, EDI_MSGF, MLM_CLEAR,0,0);
                return (MRESULT) TRUE;
                case EFATTACH:
                case EDI_ATTACH:
                   memset(&fd1, 0, sizeof(FILEDLG));
                   fd1.cbSize=sizeof(FILEDLG);
                   fd1.fl=FDS_CENTER|FDS_OPEN_DIALOG;
                   strcpy(fd1.szFullFile, "*.*");
                   fd1.pszTitle=fd1Title;
                   WinFileDlg(HWND_DESKTOP, hwnd, &fd1);
                   if(fdlg1 && (fd1.lReturn==DID_OK))
                   {
                        //WinMessageBox(HWND_DESKTOP, hwnd, fd1.szFullFile, "File Selected", 0, 0);
                        in1=fopen(fd1.szFullFile, "rb");
                        out1=fopen("uu.tmp", "w");
                        UUL=0;
                        il1=strlen(fd1.szFullFile);
                        while(fd1.szFullFile[il1]!=92)
                          il1--;
                        for(il2=0;il2<(strlen(fd1.szFullFile)-il1);il2++)
                        {
                           UUFilename[il2]=fd1.szFullFile[il1+il2+1];
                        }
                        fprintf(out1, "begin %o %s \r\n\0", 0755, UUFilename);
                        encode(in1, out1);
                        fprintf(out1, "end\n");
                        fclose(in1);
                        fclose(out1);
                        if (UUL<MaxLines)
                        {
                           WinEnableWindowUpdate(hwnd, FALSE);
                           in1=fopen("uu.tmp", "r");
                           memset(tstring4, 0, sizeof(tstring4));
                           while(filettu!=NULL)
                           {
                              filettu=fgets(tstring4, MAXLINE, in1);
                              b1=strcspn(tstring4, "\0");
                              tstring4[b1]='\r';
                              tstring4[b1+1]='\0';
                              WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_SETIMPORTEXPORT, (MPARAM)tstring4, (MPARAM)strlen(tstring4));
                              WinSendDlgItemMsg(hwnd, EDI_MSGF,MLM_IMPORT, (MPARAM)&ipt, MPFROMLONG(strlen(tstring4)));
                              for(b1=0;b1<MAXLINE;b1++)
                                 tstring4[b1]='\0';
                           }
                           WinEnableWindowUpdate(hwnd, TRUE);
                        }
                   }
                return (MRESULT) TRUE;
                }
                default: return WinDefDlgProc(hwnd, msg, parm1, parm2);
                }
                return (MRESULT)0;
}
int server_conn(void *A)
{  HWND hwnd=(HWND)A;
   char hname[MAXLINE];
   int s;
   bba.sin_port=htons(NNTP_PORT);
   bba.sin_addr.s_addr=inet_addr(hostname);
   if ((long)bba.sin_addr.s_addr == -1)
   {
      hp=gethostbyname(hostname);
      if (hp == NULL)
      {
          WinSetWindowText(hwndStatTxt, "No such computer");
          return -1;
      }
      bcopy(hp->h_addr, &bba.sin_addr, hp->h_length);
   }
   if ((s=socket(AF_INET, SOCK_STREAM, 0))<0)
   {
      WinSetWindowText(hwndStatTxt, "No socket");
      return -1;
   }
   bba.sin_family=AF_INET;
//   bba.sin_addr.s_addr=*((ULONG *)hp->h_addr);

   if (connect(s, (struct sockaddr *)&bba, sizeof(bba)) !=0)
   {
      WinSetWindowText(hwndStatTxt, "Connect error");
      return -1;
   }
   return (s);
}
VOID APIENTRY LGroup(void *A)
{
   HWND hwnd = (HWND)A;
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   if(DoneL)
   {
   WinSetWindowText(hwndStatTxt,"Loading Newsgroups...Please Wait.");
   WinEnableWindowUpdate(hwndLBALL, FALSE);
   stream7=fopen("group.lst", "r");
   if(stream7)
   {
      fgets(tstring7, MAXLINE, stream7);
      while(filetest7!=EOF)
      {
          filetest7=fscanf(stream7,"%s",&NGroups[item7].Group, &NGroups[item7].Moder);
          if ((strlen(NGroups[item7].Group))>3 && (strcspn(NGroups[item7].Group, ".")!=strlen(NGroups[item7].Group)))
          {
             GroupP[item7]=(PSZ *)NGroups[item7].Group;
             item7++;
          }
      }
      fclose(stream7);
   }
   TGroup=item7;
   memset(&lbi, 0, sizeof(lbi));
   lbi.lItemIndex=LIT_SORTASCENDING;
   lbi.ulItemCount=item7;
   WinSendMsg(hwndLBALL, LM_INSERTMULTITEMS, MPFROMP(&lbi), MPFROMP(GroupP));
   WinSetWindowText(hwndStatTxt, "Done");
   WinEnableWindowUpdate(hwndLBALL, TRUE);
   LOADED=TRUE;
   BUSY=FALSE;
   if(!ZOOMED)
   {
   WinQueryWindowRect (hwnd, &rectl);
   WinSetWindowPos(hwndLBALL, HWND_TOP, rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
   SWP_SIZE|SWP_MOVE|SWP_SHOW);
   /*
   WinSetWindowPos(hwndLBALL, HWND_TOP,
      rectl.xRight/3*2, rectl.yTop/2+offset, rectl.xRight/3,rectl.yTop/2-hChar-hBut-offset,
         SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
         WinSetWindowPos(hwndLB2, HWND_TOP,0L, 0L,0L,0L, SWP_SIZE|SWP_MOVE|SWP_SHOW);
   }
   else
   {
   WinQueryWindowRect (hwnd, &rectl);
   WinSetWindowPos(hwndLBALL, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
   }
         Subed=FALSE;
         i=TGroup;
         sprintf(Title, "All Newsgroups: %d", i);
         WinSetWindowText(hwndLB2Title,Title);
         WinPostMsg(hwnd, WM_BARUPDATE, (MPARAM)(-1),0);
         DoneL=FALSE;
   }
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   _endthread();
}

VOID APIENTRY Connect(void *A)
{
   HWND hwnd=(HWND)A;
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   int errch, nmsgs;
   ULONG Hgh, Lw,ki;
   int itemC,filetestC,itemC1;
   FILE *streamSUB;
   char tmpstring1[200];
   if(Connected)
   {
      fclose(rf);
      fclose(wf);
   }
   WinSetWindowText(hwndStatTxt, "Connecting to Server, Please Wait.");
   s8=server_conn((void *)hwnd);
   if(s8>=0)
   {
      rf8=fdopen(s8, "r");
      wf8=fdopen(s8, "a");
      fgets(tstring8, MAXLINE, rf8);
      fflush(rf8);
      if (!strncmp(tstring8, "200", 3))
         SubConn=TRUE;
   }
   s=server_conn((void *)hwnd);
   if(s>=0)
   {
      rf=fdopen(s, "r");
      wf=fdopen(s, "a");
      fgets(tstring, MAXLINE, rf);
      fflush(rf);
      if (!strncmp(tstring, "200", 3))
      {
         WinSetWindowText(hwndStatTxt, "Connection Established.");
         Connected=TRUE;
         WinSendMsg(hwndLB2, LM_DELETEALL,NULL,NULL);
         streamSUB=fopen("group.sub", "r");
         if (streamSUB)
         {
//            memset(&ListRead, 0, sizeof(ListRead));
            SubGroup=0;
            itemC1=0;
            fgets(ListRead[itemC1].Groupname,200,streamSUB);
            while(strncmp(ListRead[itemC1].Groupname, ".",1)!=0)
            {
                ki=strcspn(ListRead[itemC1].Groupname, "\n");
                ListRead[itemC1].Groupname[ki]=' ';
                ki=0;
                SubGroup++;
                BUSY=TRUE;
                WinSetWindowText(hwndStatTxt, "Updating Newsgroups..");
                fprintf(wf, "group %s\r\n",  ListRead[itemC1].Groupname);
                fflush(wf);
                fgets(tmpstring1, 200, rf);
                fflush(rf);
                sscanf(tmpstring1, "%d %d %d %d",&errch,&nmsgs,&Lw,&Hgh);
                fgets(tmpstring1, 200, streamSUB);
                while(strncmp(tmpstring1,".",1)!=0)
                {
                   sscanf(tmpstring1, "%d", &ListRead[itemC1].ListRead[ki]);
                   if ((Lw<=ListRead[itemC1].ListRead[ki])&&(ListRead[itemC1].ListRead[ki]<=Hgh))
                   {
                      ki++;
                      nmsgs--;
                   }
                   if(ListRead[itemC1].ListRead[ki]<0)
                     ki++;
                   fgets(tmpstring1, 200, streamSUB);
                }
                ListRead[itemC1].Count=ki;
                itemC=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(ListRead[itemC1].Groupname));
                if (itemC==LIT_NONE)
                {
                    if (nmsgs<0) nmsgs=0;
                    sprintf(tmpstring1, "%d", nmsgs);
                    while(5>strlen(tmpstring1))
                       strcat(tmpstring1, " ");
                    strcat(tmpstring1, ListRead[itemC1].Groupname);
                    WinSendMsg(hwndLB2, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(tmpstring1));
                    nmsgs=0;
                }
                itemC1++;
                fgets(ListRead[itemC1].Groupname,120,streamSUB);
             }
             fclose(streamSUB);
             BUSY=FALSE;
             WinSetWindowText(hwndStatTxt, "");
         }

      }
      else
      {
         fclose(rf);
         fclose(wf);
         Connected=FALSE;
         WinMessageBox(HWND_DESKTOP, hwnd, "Select Options->Connect to Server, to try again.","Connection Failed.", 0, MB_OK|MB_ERROR);
         WinSetWindowText(hwndStatTxt, "Connection Failed.");
      }
   }
   else
   {
      Connected=FALSE;
      WinMessageBox(HWND_DESKTOP, hwnd,"Select Options->Connect to Server, to try again.","Connection Failed.", 0, MB_OK|MB_ERROR);
      WinSetWindowText(hwndStatTxt, "Connection Failed.");
   }
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   _endthread();
}

VOID APIENTRY GetHeaders(void *A)
{
   HWND hwnd=(HWND)A;
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   ULONG         start,mki5;
   char KillString[256];
   int KItem3, KItem4, KCount3,kTmp;
   if (Connected)
   {
      fflush(rf);
      fprintf(wf, "group %s\r\n", groupname);
      fflush(wf);
      fgets(tstring, MAXLINE, rf);
      fflush(rf);
      if (strncmp(tstring, "2",1))
      {
         WinSetWindowText(hwndStatTxt,"No such group.");
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      mki=0;
      start=1;
      while(NULL==strstr(ListRead[mki].Groupname, groupname))
         mki++;
      for(mki5=0;mki5<ListRead[mki].Count;mki5++)
      {
         if(ListRead[mki].ListRead[mki5]<0)
            if(ListRead[mki].ListRead[mki5]<(start*-1))
               start=ListRead[mki].ListRead[mki5]*-1;
      }
//    start=ListRead[mki].Small;
      outfile=fopen("header.txt","w");
      listdone=1;
      WinSetWindowText(hwndStatTxt, "Loading Headers");
      fprintf(wf, "xhdr subject %d-\r\n",start);
      fflush(wf);
      fgets(tstring, MAXLINE,rf);
      if (!strncmp(tstring, "22", 2))
      {
         wfwrite(outfile, rf);
      }
      fflush(rf);
      WinPostMsg(hwnd, WM_BARUPDATE, (MPARAM)33,0);
      fprintf(wf, "xhdr from %d-\r\n",start);
      fflush(wf);
      fgets(tstring, MAXLINE,rf);
      if (!strncmp(tstring, "22", 2))
      {
         wfwrite(outfile, rf);
      }
      fflush(rf);
      WinPostMsg(hwnd, WM_BARUPDATE, (MPARAM)66,0);
      fprintf(wf, "xhdr lines %d-\r\n",start);
      fflush(wf);
      fgets(tstring, MAXLINE,rf);
      if (!strncmp(tstring, "22", 2))
      {
         wfwrite(outfile, rf);
      }
      fflush(rf);
      WinPostMsg(hwnd, WM_BARUPDATE, (MPARAM)100,0);
      fclose(outfile);
      WinPostMsg(hwnd, WM_BARUPDATE, (MPARAM)-1,0);
      if (SortOrd==3)
      {

         SSort();
         infile=fopen("sort.txt","r");
         if(!infile)
            infile=fopen("header.txt","r");
      }
      else
         infile=fopen("header.txt","r");
      item=0;
      tmp=fgets(tstring,MAXLINE,infile);
      if(!strncmp(tstring, "221", 3))
      {
            fgets(tstring, MAXLINE, infile);
            item=0;
            while(strncmp(tstring, ".", 1))
            {
               i=strcspn(tstring," ");
               strncpy(Head[item].Mid, tstring, i);
               Head[item].Mid[i]='\0';
               Drop(tstring, Head[item].Subject,i);
               i=strcspn(Head[item].Subject, "\n");
               Head[item].Subject[i-1]='\0';
               fgets(tstring, MAXLINE, infile);
               item++;
            }
      }
      tmp=fgets(tstring,MAXLINE,infile);
      if(!strncmp(tstring, "221", 3))
      {
          fgets(tstring, MAXLINE, infile);
          item=0;
          while(strncmp(tstring, ".", 1))
          {
             i=strcspn(tstring," ");
             Drop(tstring, Head[item].From,i+1);
             i=strcspn(Head[item].From, "\n");
             Head[item].From[i-1]='\0';
             fgets(tstring, MAXLINE, infile);
             item++;
          }
      }
      tmp=fgets(tstring,MAXLINE,infile);
      if(!strncmp(tstring, "221", 3))
      {
          fgets(tstring, MAXLINE, infile);
          item=0;
          while(strncmp(tstring, ".", 1))
          {
             i=strcspn(tstring," ");
             Drop(tstring, Head[item].Line,i+1);
             i=strcspn(Head[item].Line, "\n");
             Head[item].Line[i-1]='\0';
             fgets(tstring, MAXLINE, infile);
             item++;
          }
      }
      if(SortOrd==3)
      {
        tmp=fgets(tstring,MAXLINE,infile);
        if(!strncmp(tstring, "221", 3))
        {
          fgets(tstring, MAXLINE, infile);
          item=0;
          while(strncmp(tstring, ".", 1))
          {
             sscanf(tstring, "%s %d", tstring, &Head[item].re);
             fgets(tstring, MAXLINE, infile);
             item++;
          }
        }
      }
      fclose(infile);
   }//IF s>=0
   else
   {
      WinSetWindowText(hwndStatTxt,"Not Connected to Server.");
      WinDestroyMsgQueue(hmq);
      WinTerminate(hab);
      _endthread();
   }
   WinQueryWindowRect(hwnd, &rectl);
   if(!ZOOMED)
      WinSetWindowPos(hwndLBBlank, HWND_TOP,rectl.xRight/3, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
      SWP_SIZE|SWP_MOVE|SWP_SHOW);
                                 /*
      WinSetWindowPos(hwndLBBlank, HWND_TOP,
      rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
      SWP_SIZE|SWP_MOVE|SWP_SHOW); */
   else
      if(ZState==1)
         WinSetWindowPos(hwndLBBlank, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-20,SWP_SIZE|SWP_MOVE|SWP_SHOW);
   WinSetWindowPos(hwndLB, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
   HideArt=TRUE;
   b=item;
   item=0;
   while(NULL==strstr(ListRead[item].Groupname,groupname))
   {
     item++;
   }
   itc=item;
   strcpy(titlstr, "Article List ");
   strcat(titlstr, Head[0].Mid);
   strcat(titlstr, "-");
   strcat(titlstr, Head[b-1].Mid);
   WinSetWindowText(hwndLBTitle, titlstr);
   for(item=0;item<b;item++)
   {
      strcpy(tmpspc, " \0");
      strcat(tmpspc, Head[item].Mid);
      IGroup=tmpspc;
      while(strlen(IGroup)<=8)
        strcat(IGroup, " ");
      strcat(IGroup, Head[item].Line);
      while(strlen(IGroup)<=14)
         strcat(IGroup, " ");
      if(SortOrd==3)
      {
        if (Head[item].re>0)
        {
           for(ReC=0;ReC<Head[item].re;ReC++)
              strcat(IGroup, " -->");
           strcat(IGroup, "Re:");
        }
      }
      strcat(IGroup, Head[item].Subject);
      strcat(IGroup, " (");
      strcat(IGroup, Head[item].From);
      strcat(IGroup, ")");
      if(b!=0)
         WinPostMsg(hwnd, WM_BARUPDATE, (MPARAM)(((item+1)*100)/b),0);
     SInsert=TRUE;
     for(mki=0;mki<=ListRead[itc].Count;mki++)
     {
        if(atoi(Head[item].Mid)==ListRead[itc].ListRead[mki])
        {
           SInsert=FALSE;break;
        }
     }
     if(SInsert)
     {
        if(SortOrd==1)
           WinSendMsg(hwndLB, LM_INSERTITEM, MPFROMSHORT(LIT_SORTASCENDING),IGroup);
        if(SortOrd==2)
           WinSendMsg(hwndLB, LM_INSERTITEM, MPFROMSHORT(LIT_SORTDESCENDING),IGroup);
        if(SortOrd==3)
           WinSendMsg(hwndLB, LM_INSERTITEM, MPFROMSHORT(LIT_END),IGroup);
        SInsert=FALSE;
     }
   }
   KCount3=(int)WinSendMsg(hwndLBKill, LM_QUERYITEMCOUNT, 0,0);
   for(KItem3=0;KItem3<KCount3;KItem3++)
   {
      WinSendMsg(hwndLBKill, LM_QUERYITEMTEXT,MPFROM2SHORT(KItem3,256), MPFROMP(KillString));
      KItem4=(int)WinSendMsg(hwndLB, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(KillString));
      while(KItem4!=LIT_NONE)
      {
         kTmp=KItem4;
         KItem4=(int)WinSendMsg(hwndLB, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,kTmp),MPFROMP(KillString));
         WinSendMsg(hwndLB, LM_DELETEITEM, (MPARAM)KItem4, 0);
      }
   }
   WinQueryWindowRect(hwnd, &rectl);
   if(!ZOOMED)
      WinSetWindowPos(hwndLB, HWND_TOP,rectl.xRight/3, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
      SWP_SIZE|SWP_MOVE|SWP_SHOW);
   /*
      WinSetWindowPos(hwndLB, HWND_TOP,
      rectl.xLeft, rectl.yTop/2+offset, rectl.xRight/3*2-5, rectl.yTop/2-hChar-hBut-offset,
      SWP_SIZE|SWP_MOVE|SWP_SHOW);*/
   else
   {
      WinSetWindowPos(hwndLB, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-20,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSetWindowPos(hwndLB2, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSetWindowPos(hwndLBALL, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSetWindowPos(hwndMLE, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSetWindowPos(hwndLBUUQueue, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSetWindowPos(hwndLBKill, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)0,0);
      WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)0,0);
      WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)1,0);
      WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)0,0);
      WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)0,0);
      WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)0,0);
      ZState=1;
   }
   WinSetWindowPos(hwndLBBlank, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
   WinPostMsg(hwnd, WM_BARUPDATE, (MPARAM)-1, 0);
   WinSetWindowText(hwndStatTxt, "Done.");
   HideArt=FALSE;
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   _endthread();
}

VOID APIENTRY GetGroup(void *A)
{
   HWND hwnd=(HWND)A;
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   FILE *ggrf, *ggwf, *ggoutfile;
   int ggs, gglistdone,ggitem,space,ggitem1;
   char ggtstring[MAXLINE],gggroupname[MAXLINE],ggTitle[MAXLINE];

   ggs=server_conn((void *)hwnd);
   if(ggs>=0)
   {
      ggrf=fdopen(ggs, "r");
      ggwf=fdopen(ggs, "a");
      fgets(ggtstring, MAXLINE, ggrf);
      fflush(ggrf);
      if (!strncmp(ggtstring, "20", 2))
      {
          DoneL=FALSE;
          WinSetWindowText(hwndStatTxt, "Connection Established.");
          fputs("list\r\n", ggwf);
          fflush(ggwf);
          ggoutfile=fopen("group.lst", "w");
          gglistdone=1;
          ggitem=0;
          ggitem1=0;
          WinSetWindowText(hwndStatTxt, "Newsgroup: 0");
          while(gglistdone>0)
          {
             fgets(ggtstring, MAXLINE, ggrf);
             sscanf(ggtstring, "%s", gggroupname);
             fprintf(ggoutfile, "%s\n", gggroupname);
             fflush(ggoutfile);
             if (!strncmp(gggroupname, ".",1)) gglistdone=0;
             if (ggitem1==250)
             {
                 sprintf(ggTitle, "Newsgroup:%d", ggitem);
                 WinSetWindowText(hwndStatTxt, ggTitle);
                 ggitem1=0;
             }
             ggitem++;
             ggitem1++;
          }
          TGroup=ggitem;
          fclose(ggrf);
          fclose(ggwf);
          fclose(ggoutfile);
          WinPostMsg(hwnd,WM_LOADGPS, 0,0);
      }
      else
      {
          WinSetWindowText(hwndStatTxt, ggtstring);
      }
   }
   else
   {
      Subed=FALSE;
      WinSetWindowText(hwndStatTxt,"Error, Cannot connect to server.");
   }
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   _endthread();
}

static BOOL SetUpPage(HWND hwnd, PNBPAGE pNbPage, int nPage)
{
        ULONG ulPageId;
        HWND hwndPage, hwndNotebook;
        USHORT usPageType;
        usPageType = pNbPage->usTabType;
        hwndNotebook = WinWindowFromID(hwnd, SN_ONE);
        ulPageId = (LONG)WinSendDlgItemMsg(hwnd, SN_ONE,BKM_INSERTPAGE, NULL,
                          MPFROM2SHORT(BKA_STATUSTEXTON|BKA_AUTOPAGESIZE|usPageType,BKA_LAST));
        if (!WinSendDlgItemMsg(hwnd, SN_ONE,BKM_SETSTATUSLINETEXT, MPFROMLONG(ulPageId),
                               MPFROMP(pNbPage->szStatusLineText)))
              return FALSE;
        if (!WinSendDlgItemMsg(hwnd, SN_ONE,BKM_SETTABTEXT, MPFROMLONG(ulPageId),
                               MPFROMP(pNbPage->szTabText)))
              return FALSE;
        WinSendDlgItemMsg(hwnd, SN_ONE, BKM_SETPAGEDATA,MPFROMLONG(ulPageId),
                          MPFROMP(&nbpage[nPage]));
        if (pNbPage->pfnwpDlg != NULLHANDLE)
        {
                hwndPage = WinLoadDlg(hwnd, hwndNotebook, pNbPage->pfnwpDlg,ModuleHandle, pNbPage->idDlg, NULL);
                pNbPage->hwnd = hwndPage;
                WinSendDlgItemMsg(hwnd, SN_ONE, BKM_SETPAGEWINDOWHWND,MPFROMLONG(ulPageId), MPFROMHWND(hwndPage));
        }
        return TRUE;
}


VOID APIENTRY Mail(void *A)
{
   HWND hwnd=(HWND)A;
   int s2, listdone2;
   char tstring2[MAXLINE];
   FILE *rf2, *wf2, *infile2;
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   WinSetWindowText(hwndStatTxt, "Mailing article...Please Wait.");
   memset(&bba1, 0, sizeof(bba1));
   bba1.sin_family=AF_INET;
   hp1=gethostbyname(mailserver);
   if (hp1==NULL)
   {
      WinSetWindowText(hwndStatTxt, "Invalid Mail Server.");
      WinDestroyMsgQueue(hmq);
      WinTerminate(hab);
      _endthread();
   }
   memcpy(&bba1.sin_addr, hp1->h_addr, hp1->h_length);
   bba1.sin_port=htons(25);
   s2=socket(AF_INET, SOCK_STREAM, 0);
   if(connect(s2, (struct sockaddr *)&bba1, sizeof(bba1)) !=0)
   {
    WinSetWindowText(hwndStatTxt, "Connect Error.");
    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);
     _endthread();
   }
   if(s2>=0)
   {
      rf2=fdopen(s2, "r");
      wf2=fdopen(s2, "a");
      fgets(tstring2, MAXLINE, rf2);
      fflush(rf2);
      if (strncmp(tstring2, "220", 3))
      {
         WinSetWindowText(hwndStatTxt, "Connect Error.");
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      fputs("helo\r\n", wf2);
      fflush(wf2);
      fgets(tstring2, MAXLINE, rf2);
      fflush(rf2);
      if (!strncmp(tstring2, "22", 2))
      {
         WinSetWindowText(hwndStatTxt, "Cannot mail, Server Error.");
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      fprintf(wf2, "mail from: %s\r\n",email);
      fflush(wf2);
      fgets(tstring2, MAXLINE, rf2);
      fflush(rf2);
      if (!strncmp(tstring2, "50", 2))
      {
         WinSetWindowText(hwndStatTxt, "Cannot mail, Server Error.");
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      fprintf(wf2, "rcpt to: %s\r\n",EMailTo);
      fflush(wf2);
      fgets(tstring2, MAXLINE, rf2);
      fflush(rf2);
      if (!strncmp(tstring2, "50", 2))
      {
         WinSetWindowText(hwndStatTxt, "Cannot mail, Server Error.");
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      fprintf(wf2, "data\r\n");
      fflush(wf2);
      fgets(tstring2, MAXLINE, rf2);
      fflush(rf2);
      if (!strncmp(tstring2, "50", 2))
      {
           WinSetWindowText(hwndStatTxt, "Cannot mail, Server Error.");
           WinDestroyMsgQueue(hmq);
           WinTerminate(hab);
           _endthread();
      }
      infile2=fopen("mail.txt","r");
      listdone2=1;
      while(listdone2)
      {
         fgets(tstring2, MAXLINE, infile2);
         fprintf(wf2, "%s", tstring2);
         fflush(wf2);
         if(!strncmp(tstring2, ".", 1))
         {
            fgets(tstring2, MAXLINE, rf2);
            fflush(rf2);
            listdone2=0;

         }
      }
      if (!strncmp(tstring2, "250", 3))
           WinSetWindowText(hwndStatTxt, "Mail Successfully Sent..");
      fgets(tstring2, MAXLINE, rf2);
      fflush(rf2);
      if (strncmp(tstring2, "250", 3))
      {
           WinSetWindowText(hwndStatTxt, "Server Error, Mail Not Sent.");
           DosBeep(50,50);
      }
      else
         WinSetWindowText(hwndStatTxt, "Mail Successfully Sent..");
   }
   fclose(rf2);
   fclose(wf2);
   fclose(infile2);
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   _endthread();

}

VOID APIENTRY Post(void *A)
{
   HWND hwnd=(HWND)A;
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   int allowpost=1;
   s1=server_conn((void *)hwnd);
   if(s1>=0)
   {
      rf1=fdopen(s1, "r");
      wf1=fdopen(s1, "a");
      fgets(tstring1, MAXLINE, rf1);
      fflush(rf1);
      WinSetWindowText(hwndStatTxt, "Posting article...Please Wait.");
      if (strncmp(tstring1, "20",2))
      {
         WinSetWindowText(hwndStatTxt, "Connect to Internet First.");
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      if (strncmp(tstring1, "200",3))
         allowpost=0;
      if (!allowpost)
      {
         WinSetWindowText(hwndStatTxt, "Sorry, Cannot post.");
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      fputs("post\r\n",wf1);
      fflush(wf1);
      fgets(tstring1,MAXLINE, rf1);
      fflush(rf1);
      if(strncmp(tstring1, "340", 3))
      {
         WinSetWindowText(hwndStatTxt, "Cannot post article, Server error.");
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      listdone1=1;
      infile=fopen("post.txt","r");
      while(listdone1)
      {
        fgets(tstring1, MAXLINE, infile);
        fprintf(wf1, "%s", tstring1);
        fflush(wf1);
        if(!strncmp(tstring1, ".",1))
        {
                fgets(tstring1, MAXLINE, rf1);
                fflush(rf1);
                listdone1=0;
        }
       }
    if(!strncmp(tstring1, "441", 3))
    {
      WinSetWindowText(hwndStatTxt, "Server Error, Message Not Posted");
      DosBeep(50,50);
    }
    else
        WinSetWindowText(hwndStatTxt, "Posting Successful");
    fclose(rf1);
    fclose(wf1);
    fclose(infile);
   }
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   _endthread();
}
VOID APIENTRY GetArticle(void *A)
{
   HWND hwnd=(HWND)A;
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   if(Connected)
   {  HideArt=TRUE;
      WinSetWindowText(hwndMLE, "");
      WinPostMsg(hwnd, WM_STATMSG,(MPARAM)"Loading article...",0);
      fflush(rf);
      fprintf(wf,"group %s\r\n",groupname);
      fflush(wf);
      fgets(tstring, MAXLINE,rf);
      fflush(rf);
      if (strncmp(tstring, "2",1))
      {
         WinPostMsg(hwnd, WM_STATMSG,(MPARAM)"No such group.",0);
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
         _endthread();
      }
      if(MsgUU)
      {
      WinQueryWindowRect(hwnd, &rectl);
      if(!ZOOMED)
//      WinSetWindowPos(hwndLBBlank, HWND_TOP,0,statusbar, rectl.xRight-4, rectl.yTop,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSetWindowPos(hwndLBBlank, HWND_TOP,rectl.xLeft,rectl.yBottom+statusbar, rectl.xRight, rectl.yTop/2-hChar-statusbar+offset,
        SWP_SIZE|SWP_MOVE|SWP_SHOW);
      else
        if(ZState==3)
           WinSetWindowPos(hwndLBBlank, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-20,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSetWindowPos(hwndMLE, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      }
      outfile=fopen("head.txt", "w");
      if(outfile)
      {
         fprintf(wf, "head %s\r\n",article);
         fflush(wf);
         fgets(tstring, MAXLINE,rf);
         if (!strncmp(tstring, "22", 2))
         {
            wfwrite(outfile, rf);
         }
         fflush(wf);
         fflush(rf);
         fclose(outfile);
      }
      outfile=fopen("article.txt", "w");
      if(outfile)
      {
         fprintf(wf, "stat %s\r\n", article);
         fflush(wf);
         fgets(tstring, MAXLINE, rf);
         fflush(rf);
         if (strncmp(tstring, "2",1))
         {
            WinPostMsg(hwnd, WM_STATMSG,(MPARAM)tstring,0);
            WinDestroyMsgQueue(hmq);
            WinTerminate(hab);
            _endthread();
         }
         fprintf(wf, "body\r\n");
         fflush(wf);
         listdone=1;
         cha=0;
         chb=0;
         fgets(tstring, MAXLINE, rf);
         fgets(tstring, MAXLINE, rf);
         while (listdone)
         {
            fprintf(outfile,"%s", tstring);
            b=strcspn(tstring,"\0");
            tstring[b]='\r';
            tstring[b+1]='\0';
            WinSendMsg(hwndMLE, MLM_SETIMPORTEXPORT, (MPARAM)tstring, (MPARAM)strlen(tstring));
            WinSendMsg(hwndMLE, MLM_IMPORT, (MPARAM)&ipt, MPFROMLONG(strlen(tstring)));
            fflush(outfile);
            fgets(tstring, MAXLINE, rf);
            if(!strcmp(tstring, ".\r\n"))
            {
               WinSetWindowText(hwndStatTxt,"Done.");
               listdone=0;
            }
         }
         fclose(outfile);
      }
   }
   if(MsgUU)
   {
   WinQueryWindowRect(hwnd, &rectl);
   if(!ZOOMED)
//   WinSetWindowPos(hwndMLE, HWND_TOP,0,statusbar, rectl.xRight, rectl.yTop,SWP_SIZE|SWP_MOVE|SWP_SHOW);
    WinSetWindowPos(hwndMLE, HWND_TOP,rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop/2-hChar-statusbar+offset, SWP_SIZE|SWP_MOVE|SWP_SHOW);
   else
   {
      WinSetWindowPos(hwndMLE, HWND_TOP, rectl.xLeft, rectl.yBottom+statusbar, rectl.xRight, rectl.yTop-hBut-hChar*2-offset,SWP_SIZE|SWP_MOVE|SWP_SHOW);
      WinSetWindowPos(hwndLB, HWND_TOP, 0L,0L,0L,0L, SWP_SIZE|SWP_SHOW|SWP_SHOW);
      WinSetWindowPos(hwndLB2, HWND_TOP, 0L,0L,0L,0L, SWP_SIZE|SWP_SHOW|SWP_SHOW);
      WinSetWindowPos(hwndLBALL, HWND_TOP, 0L,0L,0L,0L, SWP_SIZE|SWP_SHOW|SWP_SHOW);
      WinSetWindowPos(hwndLBKill, HWND_TOP, 0L,0L,0L,0L, SWP_SIZE|SWP_SHOW|SWP_SHOW);
      WinSetWindowPos(hwndLBUUQueue, HWND_TOP, 0L,0L,0L,0L, SWP_SIZE|SWP_SHOW|SWP_SHOW);
      WinSendMsg(hwndZAll, BM_SETHILITE, (MPARAM)0,0);
      WinSendMsg(hwndZMsg, BM_SETHILITE, (MPARAM)1,0);
      WinSendMsg(hwndZArticle, BM_SETHILITE, (MPARAM)0,0);
      WinSendMsg(hwndZUUList, BM_SETHILITE, (MPARAM)0,0);
      WinSendMsg(hwndZKill, BM_SETHILITE, (MPARAM)0,0);
      WinSendMsg(hwndZGroups, BM_SETHILITE, (MPARAM)0,0);
      ZState=3;
   }
   WinSetWindowPos(hwndLBBlank, HWND_TOP, 0L,0L,0L,0L,SWP_SIZE|SWP_MOVE|SWP_SHOW);
   }
   HideArt=FALSE;
    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);
   _endthread();
}

void Drop(char *Source, char *Dest, int Start)
{
int it;
for(it=Start;it<strlen(Source);it++)
  Dest[it-Start]=Source[it];
//Dest[it-Start]='\0';
Dest[it-Start]='\0';
}

void wfwrite(FILE *outfile, FILE *rf)
{
    headdone=1;
    while(headdone)
    {
       fprintf(outfile, "%s", tstring);
       fflush(outfile);
       if(!strncmp(tstring, ".", 1))
       {
         headdone=0;
       }
       if (headdone)
       {
          fgets(tstring, MAXLINE, rf);
       }
    }
}

VOID APIENTRY UUDecodePrep(void *A)
{
   HWND hwnd=(HWND)A;
   int s3,i3,listdone3,a3,UUComp,pass,ic;
   int UULine;
   char drive[3]="C:";
   char fsys[16];
   BOOL FoundEnd=FALSE,FoundBegin=FALSE,FoundM=FALSE;
   char tstring3[MAXLINE], tmpstr[MAXLINE],tmpstr1[MAXLINE], DestFile[MAXLINE];
   FILE *rf3, *wf3, *outfile3, *destf,*source;
   char dest[256],UUArticleT[256];
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   Decoding=TRUE;
   s3=server_conn((void *)hwnd);
   if(s3>=0)
   {
      rf3=fdopen(s3, "r");
      wf3=fdopen(s3, "a");
      fgets(tstring3, MAXLINE,rf3);
      fflush(rf3);
      while(Paused)
      {
      DosSleep(1);
        if(Abort)
        {
            fclose(rf3);
            fclose(wf3);
            WinSendMsg(hwndLBUUQueue, LM_DELETEALL, 0,0);
            WinSetWindowText(hwndStatTxtUU, "");
            Abort=FALSE;
            FoundBegin=FALSE;
            FoundEnd=FALSE;
            Decoding=FALSE;
            WinDestroyMsgQueue(hmq);
            WinTerminate(hab);
            _endthread();
         }
      }
      while(0!=WinSendMsg(hwndLBUUQueue, LM_QUERYITEMCOUNT, 0,0))
      {
         outfile3=fopen("file.uue", "w");
      while(!FoundEnd)
      {
         fflush(rf3);
         WinSendMsg(hwndLBUUQueue, LM_QUERYITEMTEXT,MPFROM2SHORT(0,300), MPFROMP(UUArticleT));
         i3=strcspn(UUArticleT, " ");
         for(a3=0;a3<i3;a3++)
            UUArticle[a3]=UUArticleT[a3];
         UUArticle[i3]='\0';
         ic=0;
         while(0!=strcmp(UUArticle, UUNames[ic].MID))
           ic++;
         fflush(rf3);
         fprintf(wf3,"group %s\r\n",UUNames[ic].Group);
         fflush(wf3);
         fgets(tstring3, MAXLINE,rf3);
         fflush(rf3);
         if (strncmp(tstring3, "2",1))
         {
             WinSetWindowText(hwndStatTxtUU,"No such group.");
             fclose(outfile3);
             fclose(rf3);
             fclose(wf3);
             Abort=FALSE;
             FoundBegin=FALSE;
             FoundEnd=FALSE;
             Decoding=FALSE;
             WinDestroyMsgQueue(hmq);
             WinTerminate(hab);
             _endthread();
         }
         fprintf(wf3, "stat %s\r\n", UUArticle);
         fflush(wf3);
         fgets(tstring3, MAXLINE, rf3);
         fflush(rf3);
         fprintf(wf3, "xhdr lines %s\r\n", UUArticle);
         fflush(wf3);
         fgets(tstring3, MAXLINE, rf3);
         fscanf(rf3, "%s %s", tmpstr, tmpstr1);
         UULine=atoi(tmpstr1);
         fflush(rf3);
         fprintf(wf3, "body\r\n");
         fflush(wf3);
         fgets(tstring3, MAXLINE, rf3);
         if ((!FoundM)&&(FoundBegin))
         {
            while(0!=strncmp(tstring3, "M", 1))
               fgets(tstring3, MAXLINE, rf3);
            FoundM=TRUE;
         }

         if (!FoundBegin)
         {
            NoBegin=FALSE;
            listdone3=1;
            while(listdone3)
            {  fgets(tstring3, MAXLINE, rf3);
               if(strcmp(tstring3, ".\r\n")==0)
               {
                  NoBegin=TRUE;
                  listdone3=0;
               }
               if(strncmp(tstring3, "begin ", 6)==0)
                  listdone3=0;
               while(Paused)
               {
                  DosSleep(1);
                  if(Abort)
                  {
                      fclose(outfile3);
                      fclose(rf3);
                      fclose(wf3);
                      WinSendMsg(hwndLBUUQueue, LM_DELETEALL, 0,0);
                      WinSetWindowText(hwndStatTxtUU, "");
                      Abort=FALSE;
                      FoundBegin=FALSE;
                      FoundEnd=FALSE;
                      FoundM=FALSE;
                      Decoding=FALSE;
                      WinDestroyMsgQueue(hmq);
                      WinTerminate(hab);
                      _endthread();
                   }
               }
               if(Abort)
               {
                  fclose(outfile3);
                  fclose(rf3);
                  fclose(wf3);
                  WinSendMsg(hwndLBUUQueue, LM_DELETEALL, 0,0);
                  WinSetWindowText(hwndStatTxtUU, "");
                  Abort=FALSE;
                  FoundBegin=FALSE;
                  FoundEnd=FALSE;
                  FoundM=FALSE;
                  Decoding=FALSE;
                  WinDestroyMsgQueue(hmq);
                  WinTerminate(hab);
                  _endthread();
               }
            }
            FoundBegin=TRUE;
          }

          if(NoBegin)
             FoundBegin=FALSE;
          else
          {
          fputs(tstring3, outfile3);
          fflush(outfile3);
          sscanf(tstring3, "begin %*o %s",dest);
          listdone3=1;
          WinSetWindowText(hwndStatTxtUU, "Loading article...");
          WinSendMsg(hwnd, WM_BARUPDATEB, (MPARAM)-1, 0);
          fgets(tstring3, MAXLINE, rf3);
          i3=1;
          while(listdone3)
          {
             if(0==strncmp(tstring3, "begin ",6))
             {
                 strcpy(tmpstr, tstring3);
                 fclose(outfile3);
                 destf=fopen(dest, "wb");
                 if(destf!=NULL)
                 {
                 source=fopen("file.uue", "r");
                 fgets(tstring3, MAXLINE,source);
                 while(0!=strncmp(tstring3, "begin", 5))
                    fgets(tstring3, MAXLINE,source);
                 WinSetWindowText(hwndStatTxtUU, "UUDecoding Article...");
                 UUDecode(source,destf);
                 fclose(destf);
                 fclose(source);
                 }
                 else
                 {
                    WinSetWindowText(hwndStatTxtUU, "Disk Write Error");
                 }
                 outfile3=fopen("file.uue", "w");
                 sscanf(tmpstr, "begin %*o %s",dest);
                 strcpy(tstring3,tmpstr);
              }
             i3++;
             if(UULine!=0)
             {
                UUComp=i3*100/UULine;
                if((UUComp % 5)==0)
                {
                   sprintf(tmpstr, "%d%% Completed.",UUComp);
                   if (0!=strcmp(tmpstr, tmpstr1))
                   {strcpy(tmpstr1,tmpstr);
                    WinSendMsg(hwndUUProgress,SM_SETHANDLE ,(MPARAM)hbm[UUComp/5],0);
                    WinSendMsg(hwnd, WM_BARUPDATEB, (MPARAM)UUComp, 0);
                   }
                }
             }
             if(Abort)
             {
                 fclose(outfile3);
                 fclose(rf3);
                 fclose(wf3);
                 WinSendMsg(hwndLBUUQueue, LM_DELETEALL, 0,0);
                 WinSetWindowText(hwndStatTxtUU, "");
                 Abort=FALSE;
                 FoundBegin=FALSE;
                 FoundEnd=FALSE;
                 FoundM=FALSE;
                 Decoding=FALSE;
                 WinDestroyMsgQueue(hmq);
                 WinTerminate(hab);
                 _endthread();
              }
             if(0!=strncmp(tstring3, " ",7))
               fprintf(outfile3, "%s",tstring3);
             fgets(tstring3, MAXLINE, rf3);
             fflush(outfile3);
             if(!strcmp(tstring3, ".\r\n"))
             {
                listdone3=0;
                FoundM=FALSE;
             }
             if(!strncmp(tstring3, "end",3))
                 FoundEnd=TRUE;
             while(Paused)
             {

                 DosSleep(1);
                 if(Abort)
                 {
                     fclose(outfile3);
                     fclose(rf3);
                     fclose(wf3);
                     WinSendMsg(hwndLBUUQueue, LM_DELETEALL, 0,0);
                     WinSetWindowText(hwndStatTxtUU, "");
                     Abort=FALSE;
                     FoundBegin=FALSE;
                     FoundEnd=FALSE;
                     Decoding=FALSE;
                     WinDestroyMsgQueue(hmq);
                     WinTerminate(hab);
                     _endthread();
                  }
             }
          }
          }
          WinSendMsg(hwndLBUUQueue, LM_DELETEITEM, MPFROMSHORT(0),0);
       }
       fclose(outfile3);
       strcpy(DestFile, DownloadDir);
       strcat(DestFile, "\\");
       strcat(DestFile, dest);
       destf=fopen(DestFile, "wb");
       if(destf)
       {
       source=fopen("file.uue", "r");
       while(0!=strncmp(tstring3, "begin", 5))
          fgets(tstring3, MAXLINE,source);
       WinSendMsg(hwndUUProgress,SM_SETHANDLE ,(MPARAM)hbm[0],0);
       WinSetWindowText(hwndStatTxtUU, "UUDecoding Article...");
       UUDecode(source,destf);
       if(UUDownBeep==1)
          DosBeep(500,500);
       FoundBegin=FALSE;
       FoundEnd=FALSE;
       fclose(destf);
       fclose(source);
       WinSetWindowText(hwndStatTxtUU, "Done.");
       }
       else
           WinSetWindowText(hwndStatTxtUU, "Disk Write Error...");
    }
    fclose(wf3);
    fclose(rf3);
   }
   Decoding=FALSE;
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   _endthread();
}
VOID APIENTRY UUDecode(FILE *source,FILE *destf)
{
   char buf[80];
   char *bp;
   int n,v, expected;
   for(;;)
   {
      if (fgets(buf, sizeof buf, source)==NULL)
      {
         WinSetWindowText(hwndStatTxtUU, "Short file");
         return;
      }
      if (buf[0]=='\n')
         continue;
      n=DEC(buf[0]);
      if(n<=0)
         break;
      expected=((n+2)/3)<<2;
      for(v=strlen(buf)-1;v<=expected;v++) buf[v]=' ';
      bp=&buf[1];
      while(n>0)
      {
        outdec(bp, destf, n);
        bp+=4;
        n-=3;
      }
   }
}
void outdec(char *p, FILE *f, int n)
{
   int c1,c2,c3;
   c1 = DEC(*p) << 2 | DEC(p[1]) >> 4;
   c2 = DEC(p[1]) << 4 | DEC(p[2]) >> 2;
   c3 = DEC(p[2]) << 6 | DEC(p[3]);
   if (n >= 1)
        putc(c1, f);
   if (n >= 2)
        putc(c2, f);
   if (n >= 3)
        putc(c3, f);
}
char * index(char * sp, char c)
{
        while(*sp)
        {
           if (*sp == c)return(sp);
               sp++;
        }
    return(0);
}
void encode(FILE *in, FILE *out)
{
   char buf[80];
   register int i4,n4;
   for(;;)
   {
      n4=fread(buf, 1, 45, in);
      putc(ENC(n4),out);
      for(i4=0;i4<n4;i4+=3)
      {
         outdecen(&buf[i4], out);
      }
      fputs("\r\n\0", out);
      UUL++;
      if (n4<=0)
         break;
    }
}
void outdecen(char *p, FILE *f)
{
   register int c1,c2,c3,c4;
   c1=*p>>2;
   c2 = (*p << 4) & 060 | (p[1] >> 4) & 017;
   c3 = (p[1] << 2) & 074 | (p[2] >> 6) & 03;
   c4 = p[2] & 077;
   putc(ENC(c1), f);putc(ENC(c2), f);
   putc(ENC(c3), f);putc(ENC(c4), f);
}
VOID APIENTRY StartBr(void *A)
{
   char *CmdLine1=(char *)A;
   system(CmdLine1);
   _endthread;
}
VOID APIENTRY Subscribe(void *A)
{
   HWND hwnd=(HWND)A;
   HAB           hab = WinInitialize(0);
   HMQ           hmq = WinCreateMsgQueue(hab, 0L);
   if(DoneSub)
   {
      DoneSub=FALSE;
      if (SubConn)
      {
          ki8=SubGroup;
          strcpy(ListRead[ki8].Groupname,groupname);
          WinSetWindowText(hwndStatTxt, "Subscribing..");
          SubGroup++;
          fprintf(wf8, "group %s\r\n",  groupname);
          fflush(wf8);
          fgets(tmpstring8, 200, rf8);
          fflush(rf8);
          sscanf(tmpstring8, "%d %d %d %d",&errch8,&nmsgs8,&Hgh8,&Lw8);
          item=(int)WinSendMsg(hwndLB2, LM_SEARCHSTRING, MPFROM2SHORT(LSS_SUBSTRING,LIT_FIRST),MPFROMP(groupname));
          if (item==LIT_NONE)
          {
              sprintf(tmpstring8, "%d", nmsgs8);
              while(5>strlen(tmpstring8))
              strcat(tmpstring8, " ");
              strcat(tmpstring8, ListRead[ki8].Groupname);
              strcat(tmpstring8, " ");
              WinSendMsg(hwndLB2, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(tmpstring8));
              WinSetWindowText(hwndStatTxt,"Subscribed.");
              Changed();
          }
          else
            WinSetWindowText(hwndStatTxt, tstring8);
      }
      else
          WinSetWindowText(hwndStatTxt, "No Connection Made.");
      DoneSub=TRUE;
   }
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   _endthread();
}

static BOOL TurnToFirstPage(HWND hwndClient)
{
   HWND hwndNB=WinWindowFromID(hwndClient, SN_ONE);
   ULONG ulFirstPage;
   BOOL fSuccess = TRUE;
   ulFirstPage=(ULONG) WinSendMsg(hwndNB, BKM_QUERYPAGEID, NULL, MPFROM2SHORT(BKA_FIRST, BKA_MAJOR));
   fSuccess=(BOOL)WinSendMsg(hwndNB, BKM_TURNTOPAGE, MPFROMLONG(ulFirstPage), NULL);
}

static BOOL SetTabDimensions(HWND hwndNB)
{
        BOOL fSuccess=TRUE;
        HPS  hps=WinGetPS(hwndNB);
        FONTMETRICS fm;
        INT h,iSize,iLongestMajText=0,iLongestMinText=0;
        memset(&fm, 0,sizeof(FONTMETRICS));
        if(GpiQueryFontMetrics(hps, sizeof(FONTMETRICS), &fm))
           fm.lMaxBaselineExt +=(6*2);
        else
           fm.lMaxBaselineExt = 16 + (6*2);
        for(h=0;h<PAGE_COUNT;h++)
        {
         iSize=GetStringSize(hps, hwndNB, nbpage[h].szTabText);
         if(nbpage[h].usTabType=BKA_MAJOR)
         {
           if(iSize>iLongestMajText)
              iLongestMajText=iSize;
         }
         else
         {
           if(iSize>iLongestMinText)
              iLongestMinText=iSize;
         }
        }
        WinReleasePS(hps);
        if(iLongestMajText)
          iLongestMajText+=10;
        if(iLongestMinText)
          iLongestMinText+=10;
        if(iLongestMajText)
        {
                fSuccess=(BOOL)WinSendMsg(hwndNB,BKM_SETDIMENSIONS, MPFROM2SHORT(iLongestMajText,
                         (SHORT)fm.lMaxBaselineExt),MPFROMSHORT(BKA_MAJORTAB));
                fSuccess=(BOOL)WinSendMsg(hwndNB, BKM_SETDIMENSIONS, MPFROM2SHORT(iLongestMinText,
                         (SHORT)fm.lMaxBaselineExt),MPFROMSHORT(BKA_MINORTAB));
         }
return fSuccess;
}
static INT  GetStringSize(HPS hps, HWND hwndNoteBook, PSZ szString)
{
        POINTL aptl[TXTBOX_COUNT];
        if(!GpiQueryTextBox(hps, strlen(szString), szString, TXTBOX_COUNT, aptl))
         return 0;
        else
         return aptl[TXTBOX_CONCAT].x;
}
MRESULT EXPENTRY wpPage1(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
         switch(msg)
         {
                 case WM_SAVESETTINGS:
                        WinQueryDlgItemText(hwnd, SET_NEWSF, 1000, hostname);
                        WinQueryDlgItemText(hwnd, SET_MAILSF, 1000, mailserver);
                        WinQueryDlgItemText(hwnd, SET_NAMEF, 1000,realn);
                        WinQueryDlgItemText(hwnd, SET_EMAILF, 1000,email);
                        WinQueryDlgItemText(hwnd, SET_ORGF,1000,organ);
                 break;
                 case WM_INITDLG:
                          WinSendDlgItemMsg(hwnd, SET_NEWSF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
                          WinSendDlgItemMsg(hwnd, SET_MAILSF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
                          WinSendDlgItemMsg(hwnd, SET_EMAILF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
                          WinSendDlgItemMsg(hwnd, SET_NAMEF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
                          WinSendDlgItemMsg(hwnd, SET_ORGF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
                          WinSetDlgItemText(hwnd, SET_NEWSF, hostname);
                          WinSetDlgItemText(hwnd, SET_MAILSF, mailserver);
                          WinSetDlgItemText(hwnd, SET_EMAILF, email);
                          WinSetDlgItemText(hwnd, SET_NAMEF, realn);
                          WinSetDlgItemText(hwnd, SET_ORGF, organ);
                 break;
                 case WM_COMMAND:
                  switch(SHORT1FROMMP(parm1)){
                    case NBP1_CANCEL:
                    DosBeep(500,500);
                    WinSendMsg(nbpage[0].hwnd,WM_QUIT,0,0);
                    break;

                    }

                         return 0;
         }
    return WinDefDlgProc(hwnd,msg,parm1,parm2);
}
MRESULT EXPENTRY wpPage2(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
char wptstring[256],*wpfile;
FILE *wpstream;
int  wp3i;
        switch(msg)
        {
                case WM_INITDLG:
                wpstream=fopen("newsbeat.sig", "r");
                if (wpstream)
                {
                while(wpfile!=NULL)
                {
                wpfile=fgets(wptstring, 256, wpstream);
                wp3i=strcspn(wptstring, "\0");
                wptstring[wp3i]='\r';
                wptstring[wp3i+1]='\0';
                WinSendDlgItemMsg(hwnd, NBP2_SIGF,MLM_SETIMPORTEXPORT, (MPARAM)wptstring, (MPARAM)strlen(wptstring));
                WinSendDlgItemMsg(hwnd, NBP2_SIGF,MLM_IMPORT, (MPARAM)&ipt, MPFROMLONG(strlen(wptstring)));
                }
                fclose(wpstream);
                }
                break;
                case WM_SAVESETTINGS:
                wpstream=fopen("newsbeat.sig", "w");
                lOffset=0;
                memset(szMleBuf, 0, sizeof(szMleBuf));
                WinSendDlgItemMsg(hwnd, NBP2_SIGF, MLM_SETIMPORTEXPORT, MPFROMP(szMleBuf), MPFROMSHORT((USHORT)sizeof(szMleBuf)));
                cbCopy=(ULONG)WinSendDlgItemMsg(hwnd, NBP2_SIGF, MLM_QUERYFORMATTEXTLENGTH, MPFROMLONG(lOffset), MPFROMLONG((-1)));
                while(cbCopy!=0)
                {
                   WinSendDlgItemMsg(hwnd, NBP2_SIGF, MLM_EXPORT, MPFROMP(&lOffset), MPFROMP(&cbCopy));
                   fputs(szMleBuf,wpstream);
                   for(wp3i=0;wp3i<sizeof(szMleBuf);wp3i++)
                   szMleBuf[wp3i]='\0';
                }
                fclose(wpstream);
                for(wp3i=0;wp3i<sizeof(szMleBuf);wp3i++)
                szMleBuf[wp3i]='\0';
                break;
                case WM_COMMAND:
                        return 0;
        }
        return WinDefDlgProc(hwnd,msg,parm1,parm2);
}
MRESULT EXPENTRY wpPage3(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
char wptstringz[256],*wpfilez;
FILE *wpstreamz;
int  wp3iz;
        switch(msg)
        {
               case WM_SAVESETTINGS:
               WinQueryDlgItemText(hwnd, SET_PUUDF, 256,DownloadDir);
               if(WinQueryButtonCheckstate(hwnd, NBP3_ASC))
                  SortOrd=1;
               if(WinQueryButtonCheckstate(hwnd, NBP3_DEC))
                  SortOrd=2;
               if(WinQueryButtonCheckstate(hwnd, NBP3_THR))
                  SortOrd=3;
               if(WinQueryButtonCheckstate(hwnd, NBP3_BEEP))
                  UUDownBeep=1;
               else
                  UUDownBeep=0;
               wpstreamz=fopen("news.rc", "w");
                  fprintf(wpstreamz,"%s\n", hostname);
                  fprintf(wpstreamz,"%s\n", mailserver);
                  fprintf(wpstreamz,"%s\n", email);
                  fprintf(wpstreamz,"%s\n", realn);
                  fprintf(wpstreamz,"%s\n", organ);
                  fprintf(wpstreamz,"%d\n", TGroup);
                  fprintf(wpstreamz, "%d\n", SortOrd);
                  fprintf(wpstreamz, "%d\n", FastLoad);
                  fprintf(wpstreamz, "%s\n", DownloadDir);
                  fprintf(wpstreamz, "%d\n", UUDownBeep);
                  fprintf(wpstreamz, "%s\n", RegName);
                  fprintf(wpstreamz, "%d\n", Key);
                  fprintf(wpstreamz, "%d\n", Code);
               fclose(wpstreamz);
                     break;
               case WM_INITDLG:
                        WinSendDlgItemMsg(hwnd, SET_PUUDF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
                        if(SortOrd==1)
                          WinSendDlgItemMsg(hwnd, NBP3_ASC, BM_SETCHECK,MPFROMP(TRUE), 0);
                        if(SortOrd==2)
                          WinSendDlgItemMsg(hwnd, NBP3_DEC, BM_SETCHECK,MPFROMP(TRUE), 0);
                        if((SortOrd>2)||(SortOrd<1))
                          WinSendDlgItemMsg(hwnd, NBP3_THR, BM_SETCHECK,MPFROMP(TRUE), 0);
                        if(UUDownBeep==1)
                           WinSendDlgItemMsg(hwnd, NBP3_BEEP, BM_SETCHECK,MPFROMP(TRUE), 0);
                        WinSetDlgItemText(hwnd, SET_PUUDF, DownloadDir);

                break;
                case WM_COMMAND:
                        return 0;
        }
        return WinDefDlgProc(hwnd,msg,parm1,parm2);
}
MRESULT EXPENTRY wpPage4(HWND hwnd, ULONG msg, MPARAM parm1, MPARAM parm2)
{
   char wptstringy[256],*wpfiley;
   FILE *wpstreamy;
   int  wp3iy;

        switch(msg)
        {
                case WM_INITDLG:
                   WinSendDlgItemMsg(hwnd, NBP4_BRF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
                   WinSendDlgItemMsg(hwnd, NBP4_PARF, EM_SETTEXTLIMIT,MPFROMSHORT(256),0);
                   WinSetDlgItemText(hwnd, NBP4_BRF, Browser);
                   WinSetDlgItemText(hwnd, NBP4_PARF, Params);
                break;
                case WM_SAVESETTINGS:
                        WinQueryDlgItemText(hwnd, NBP4_BRF, 256,Browser);
                        WinQueryDlgItemText(hwnd, NBP4_PARF, 100,Params);
                        wpstreamy=fopen("newsbeat.vwr", "w");
                           fprintf(wpstreamy, "%s\n", Browser);
                           fprintf(wpstreamy, "%s\n", Params);
                           fprintf(wpstreamy, ".\n");
                        fclose(wpstreamy);
                   break;
                case WM_COMMAND:
                        return 0;
        }
        return WinDefDlgProc(hwnd,msg,parm1,parm2);
}

VOID Changed(void)
{
   int kj;
   stream2s=fopen("group.sub", "w");
   for(j=0;j<SubGroup;j++)
   {
      if(ListRead[j].Groupname[0]!='\0')
      {
         fprintf(stream2s,"%s\n", ListRead[j].Groupname);
         for(kj=0;kj<ListRead[j].Count;kj++)
         {
            if(ListRead[j].ListRead[kj]!=0)
               fprintf(stream2s, "%d\n",ListRead[j].ListRead[kj]);
         }
         fprintf(stream2s, ".\n");
      }
   }
   fprintf(stream2s, ".\n");
   fclose(stream2s);
}
VOID APIENTRY SSort(VOID)
{
    FILE *Srf, *Swf;
    char Sstring[1000],subjtemp[MAXLINE];
    int Sx,Sc;
    Sx=1;
    do
        Srf=fopen("header.txt", "r");
    while(!Srf);
    WinSetWindowText(hwndStatTxt, "Sorting Messages.");
    fgets(Sstring, 1000, Srf);
    fgets(Sstring, 1000, Srf);
    while (strncmp(Sstring, ".",1))
    {
        if(strlen(Sstring)>256)
           strncpy(Sstring, Sstring, 256);
        strcpy(Head[Sx].Mid, strtok(Sstring, " "));
        strcpy(Head[Sx].Subject, strtok('\0', "\r"));
        Head[Sx].re=0;
        while (!strnicmp(Head[Sx].Subject, "re:", 3))
        {
           strcpy(subjtemp, &Head[Sx].Subject[4]);
           strcpy(Head[Sx].Subject, subjtemp);
           Head[Sx].re++;
        }
        Sx++;
        fgets(Sstring, 1000, Srf);
    }
    fgets(Sstring, MAXLINE, Srf);
    Sx=1;
    fgets(Head[Sx].From, MAXLINE, Srf);
    while (strncmp(Head[Sx].From, ".",1))
    {
       Sx++;
       fgets(Head[Sx].From, MAXLINE, Srf);
    }
    fgets(Sstring, MAXLINE, Srf);
    Sx=1;
    fgets(Head[Sx].Line, MAXLINE, Srf);
    while (strncmp(Head[Sx].Line, ".",1))
    {
       Sx++;
       fgets(Head[Sx].Line, MAXLINE, Srf);
    }
    fclose(Srf);
    Sx--;
    WinSetWindowText(hwndStatTxt, "Sorting Messages.");
    ShellSort(1,Sx);
    WinSetWindowText(hwndStatTxt, "Writting.");
    Swf=fopen("sort.txt", "w");
    fprintf(Swf, "221 subject fields follow\n");
    for(Sc=1;Sc<Sx;Sc++)
      fprintf(Swf, "%s %s\r\n",Head[Sc].Mid, Head[Sc].Subject);
    fprintf(Swf, ".\n221 from fields follow\n");
    for(Sc=1;Sc<Sx;Sc++)
      fputs(Head[Sc].From, Swf);
    fprintf(Swf, ".\n221 lines fields follow\n");
    for(Sc=1;Sc<Sx;Sc++)
       fputs(Head[Sc].Line, Swf);
    fprintf(Swf, ".\n221 re fields follow\n");
    for(Sc=1;Sc<Sx;Sc++)
        fprintf(Swf,"%s %d\n",Head[Sc].Mid, Head[Sc].re);
    fprintf(Swf, ".\n");
    fclose(Swf);
    WinSetWindowText(hwndStatTxt, "Done");
}
static void ShellSort(int LowH, int MaxH)
{
   int d, i, j;
   Headers ssv;
   for (d=MaxH-LowH+1;d>1;)
   {
      if(d<5) d=1;
      else d=(5*d-1)/11;
      for (i=MaxH-d; i>=LowH; i--)
      {
         ssv=Head[i];
         for(j=i+d;j<=MaxH && (0<stricmp(ssv.Subject,Head[j].Subject)); j+=d)
            Head[j-d] = Head[j];
         Head[j-d]=ssv;
      }
   }



}
static BOOL Encrypt(char s1[MAXLINE], ULONG sn3,ULONG sn4)
{
   unsigned long long int k1=0, k2=0,sn1=0 ,sn2=0;
   unsigned long long int x;
   k1=185495;
   k2=637901;
   for(x=0; x<strlen(s1); x++)
   {
      sn1=sn1+s1[x];
   }
   while (sn1<1000)
   {
      sn1=sn1*2;
   }
   sn2=sn1*k1;
   sn2=sn2>>2;
   sn2=sn2+k2;
   sn2=sn2|k1;
   sn2=sn2<<3;
   sn2=sn2 & k2;
   if ((sn1==sn3) && (sn2==sn4))
     return TRUE;
   else
     return FALSE;
}





