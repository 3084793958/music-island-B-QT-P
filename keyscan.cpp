#include "keyscan.h"
#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <X11/extensions/record.h>

static Display * m_display;
static XRecordRange * range;
static XRecordContext m_context;
static XRecordClientSpec clients;

static void recordEventCallback(char *, XRecordInterceptData *);

keyScan::keyScan(QObject *parent)
    : QThread( parent )
{
    registerd();
}

keyScan::~keyScan()
{
    unregister();
}

void keyScan::registerd()
{
    Display * display =XOpenDisplay(nullptr);
    clients = XRecordAllClients;
    range = XRecordAllocRange();
    memset(range, 0, sizeof(XRecordRange));
    range->device_events.first = KeyPress;
    range->device_events.last  = MotionNotify;
    m_context = XRecordCreateContext( display, 0, &clients, 1,&range, 1 );

    XFree(range);
    XSync( display, False );
    m_display = XOpenDisplay(nullptr);
}

void keyScan::run()
{
    XRecordEnableContext( m_display, m_context,recordEventCallback,reinterpret_cast<XPointer>(this));
}


void recordEventCallback(char * ptr, XRecordInterceptData * data )
{

    if ( data->category == XRecordFromServer )
    {
        data->client_swapped = false;
        xEvent * event = reinterpret_cast<xEvent *>(data->data);
        switch (event->u.u.type) {
        case ButtonPress:
        {
            emit reinterpret_cast<keyScan*>(ptr)->sig_buttonPressed(event->u.u.detail);
        }
            break;
        case ButtonRelease:
        {
            emit reinterpret_cast<keyScan*>(ptr)->sig_buttonRelease(event->u.u.detail);
        }
            break;
        case KeyPress:
        {
            emit reinterpret_cast<keyScan*>(ptr)->sig_keyPressed((static_cast<unsigned char*>(data->data))[1]);
        }
            break;    
        case KeyRelease:
        {
            emit reinterpret_cast<keyScan*>(ptr)->sig_keyRelease((static_cast<unsigned char*>(data->data))[1]);
        }
            break;
        default:
            break;
        }
    }
    XRecordFreeData( data );
}

void keyScan::unregister()
{
    Display * display = XOpenDisplay(nullptr);
    XRecordDisableContext( display, m_context );
    XSync( display, 0 );
    wait();
    XRecordFreeContext( display, m_context );
    XCloseDisplay(m_display );
}
