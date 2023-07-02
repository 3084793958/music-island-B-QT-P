#include "keyscan.h"
#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <X11/extensions/record.h>

Display * m_display;
XRecordRange * range;
XRecordContext m_context;
XRecordClientSpec clients;

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
    XRecordEnableContext( m_display, m_context,recordEventCallback,(XPointer)this);
}


void recordEventCallback(char * ptr, XRecordInterceptData * data )
{

    if ( data->category == XRecordFromServer )
    {
        data->client_swapped = false;
        xEvent * event = (xEvent *) data->data;
        switch (event->u.u.type) {
        case ButtonPress:
        {
            emit ((keyScan*)ptr)->sig_buttonPressed(event->u.u.detail);
        }
            break;
        case KeyPress:
        {
            emit ((keyScan*)ptr)->sig_keyPressed(((unsigned char*)data->data)[1]);
        }
            break;    
        case KeyRelease:
        {
            emit ((keyScan*)ptr)->sig_keyRelease(((unsigned char*)data->data)[1]);
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
