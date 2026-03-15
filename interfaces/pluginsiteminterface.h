// SPDX-FileCopyrightText: 2011 - 2022 UnionTech Software Technology Co., Ltd.
// SPDX-FileCopyrightText: 2026 github.com:3084793958
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef PLUGINSITEMINTERFACE_H
#define PLUGINSITEMINTERFACE_H

#include "pluginproxyinterface.h"

#include <QIcon>
#include <QtCore>

#include <QMenu>

//for Easy_Desktop
struct P_Version
{
    uint Major_Version;
    uint Minor_Version;
    uint Patch_Version;
    P_Version(uint m_Major_Version, uint m_Minor_Version, uint m_Patch_Version);
    bool operator==(P_Version m_version) const;
    bool operator!=(P_Version m_version) const;
    bool operator>(P_Version m_version) const;
    bool operator>=(P_Version m_version) const;
    bool operator<(P_Version m_version) const;
    bool operator<=(P_Version m_version) const;
    QString VersionName() const;
};
class P_Sender : public QObject
{
    Q_OBJECT
public:
    explicit P_Sender(QObject *parent = nullptr, bool m_allow_Send_Data = true, bool m_allow_Send_Ptr = true);
    void Send();
    void Send_Data(QVariant var);
    void Send_Ptr(void *ptr);
    bool allow_Send_Data = true;
    bool allow_Send_Ptr = true;
signals:
    void sig_Send();
    void sig_Send_Data(QVariant var);
    void sig_Send_Ptr(void *ptr);
};
//for Easy_Desktop

///
/// \brief The PluginsItemInterface class
/// the dock plugins item interface, all dock plugins should
/// inheirt this class and override all pure virtual function.
///
class PluginsItemInterface
{
public:
    enum PluginType {
        Normal,
        Fixed
    };

    //插件需要在json中说明自己支持Ext
    //ADD
    const QString Ext_Name = "Easy_Desktop";
    const QString Ext_Spec = "";
    //ADD

    //for Easy_Desktop
    P_Version Plugin_Version{0, 0, 1};//不使用const,用于欺骗Easy_Desktop
    //最低版本号:0.0.1
    //for Easy_Desktop

    /**
    * @brief Plugin size policy
    */
    enum PluginSizePolicy {
        System = 1 << 0, // Follow the system
        Custom = 1 << 1  // The custom
    };

    ///
    /// \brief ~PluginsItemInterface
    /// DON'T try to delete m_proxyInter.
    ///
    virtual ~PluginsItemInterface() {}

    ///
    /// \brief pluginName
    /// tell dock the unique plugin id
    /// \return
    ///
    virtual const QString pluginName() const = 0;
    virtual const QString pluginDisplayName() const { return QString(); }

    ///
    /// \brief init
    /// init your plugins, you need to save proxyInter to m_proxyInter
    /// member variable. but you shouldn't free this pointer.
    /// \param proxyInter
    /// DON'T try to delete this pointer.
    ///
    virtual void init(PluginProxyInterface *proxyInter) = 0;
    ///
    /// \brief itemWidget
    /// your plugin item widget, each item should have a unique key.
    /// \param itemKey
    /// your widget' unqiue key.
    /// \return
    ///
    virtual QWidget *itemWidget(const QString &itemKey) = 0;

    ///
    /// \brief itemTipsWidget
    /// override this function if your item want to have a tips.
    /// the tips will shown when user hover your item.
    /// nullptr will be ignored.
    /// \param itemKey
    /// \return
    ///
    virtual QWidget *itemTipsWidget(const QString &itemKey) {Q_UNUSED(itemKey); return nullptr;}
    ///
    /// \brief itemPopupApplet
    /// override this function if your item wants to have an popup applet.
    /// the popup applet will shown when user click your item.
    ///
    /// Tips:
    /// dock should receive mouse press/release event to check user mouse operate,
    /// if your item filter mouse event, this function will not be called.
    /// so if you override mouse event and want to use popup applet, you
    /// should pass event to your parent use QWidget::someEvent(e);
    /// \param itemKey
    /// \return
    ///
    virtual QWidget *itemPopupApplet(const QString &itemKey) {Q_UNUSED(itemKey); return nullptr;}
    ///
    /// \brief itemCommand
    /// execute spec command when user clicked your item.
    /// ensure your command do not get user input.
    ///
    /// empty string will be ignored.
    /// \param itemKey
    /// \return
    ///
    virtual const QString itemCommand(const QString &itemKey) {Q_UNUSED(itemKey); return QString();}

    ///
    /// \brief itemContextMenu
    /// context menu is shown when RequestPopupMenu called.
    /// \param itemKey
    /// \return
    ///
    virtual const QString itemContextMenu(const QString &itemKey) {Q_UNUSED(itemKey); return QString();}
    ///
    /// \brief invokedMenuItem
    /// call if context menu item is clicked
    /// \param itemKey
    /// \param itemId
    /// menu item id
    /// \param checked
    ///
    virtual void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) {Q_UNUSED(itemKey); Q_UNUSED(menuId); Q_UNUSED(checked);}

    ///
    /// \brief itemSortKey
    /// tell dock where your item wants to put on.
    ///
    /// this index is start from 1 and
    /// 0 for left side
    /// -1 for right side
    /// \param itemKey
    /// \return
    ///
    virtual int itemSortKey(const QString &itemKey) {Q_UNUSED(itemKey); return 1;}
    ///
    /// \brief setSortKey
    /// save your item new position
    /// sort key will be changed when plugins order
    /// changed(by user drag-drop)
    /// \param itemKey
    /// \param order
    ///
    virtual void setSortKey(const QString &itemKey, const int order) {Q_UNUSED(itemKey); Q_UNUSED(order);}

    ///
    /// \brief itemAllowContainer
    /// tell dock is your item allow to move into container
    ///
    /// if your item placed into container, popup tips and popup
    /// applet will be disabled.
    /// \param itemKey
    /// \return
    ///
    virtual bool itemAllowContainer(const QString &itemKey) {Q_UNUSED(itemKey); return false;}
    ///
    /// \brief itemIsInContainer
    /// tell dock your item is in container, this function
    /// called at item init and if your item enable container.
    /// \param itemKey
    /// \return
    ///
    virtual bool itemIsInContainer(const QString &itemKey) {Q_UNUSED(itemKey); return false;}
    ///
    /// \brief setItemIsInContainer
    /// save your item new state.
    /// this function called when user drag out your item from
    /// container or user drop item into container(if your item
    /// allow drop into container).
    /// \param itemKey
    /// \param container
    ///
    virtual void setItemIsInContainer(const QString &itemKey, const bool container) {Q_UNUSED(itemKey); Q_UNUSED(container);}

    virtual bool pluginIsAllowDisable() { return false; }
    virtual bool pluginIsDisable() { return false; }
    virtual void pluginStateSwitched() {}

    ///
    /// \brief displayModeChanged
    /// override this function to receive display mode changed signal
    /// \param displayMode
    ///
    virtual void displayModeChanged(const Dock::DisplayMode displayMode) {Q_UNUSED(displayMode);}
    ///
    /// \brief positionChanged
    /// override this function to receive dock position changed signal
    /// \param position
    ///
    virtual void positionChanged(const Dock::Position position) {Q_UNUSED(position);}

    ///
    /// \brief refreshIcon
    /// refresh item icon, its triggered when system icon theme changed.
    /// \param itemKey
    /// item key
    ///
    virtual void refreshIcon(const QString &itemKey) { Q_UNUSED(itemKey); }

    ///
    /// \brief displayMode
    /// get current dock display mode
    /// \return
    ///
    inline Dock::DisplayMode displayMode() const
    {
        return qApp->property(PROP_DISPLAY_MODE).value<Dock::DisplayMode>();
    }

    ///
    /// \brief position
    /// get current dock position
    /// \return
    ///
    inline Dock::Position position() const
    {
        return qApp->property(PROP_POSITION).value<Dock::Position>();
    }

    ///
    /// \brief settingsChanged
    /// override this function to receive plugin settings changed signal(DeepinSync)
    ///
    virtual void pluginSettingsChanged() {}

    ///
    /// \brief type
    /// default plugin add dock right,fixed plugin add to dock fixed area
    ///
    virtual PluginType type() { return Normal; }

    ///
    /// \brief plugin size policy
    /// default plugin size policy
    ///
    virtual PluginSizePolicy pluginSizePolicy() const { return System; }

    //for Easy_Desktop 0.0.1
    virtual bool pluginIsAllowUnload() { return false; }
    virtual void pluginUnload() {}
    //
    enum class Carrier_Type
    {
        Unknown,
        Plugin_Item,
        Plugin_Popup,
        Plugin_Tips
    };
    virtual void pluginGetSender(P_Sender * const update_sender, P_Sender * const send_data_sender)
    {
        (void) update_sender;
        (void) send_data_sender;
    }
    virtual QPair<int, int> pluginSetCarrierSpacing(Carrier_Type carrier_type, bool *isValid)
    {
        (void) carrier_type;
        *isValid = false;
        return qMakePair(0, 0);
    }
    virtual void pluginGetCarrierSpacing(Carrier_Type carrier_type, int distance_width, int distance_height)
    {
        (void) carrier_type;
        (void) distance_width;
        (void) distance_height;
    }
    virtual QPair<int, int> pluginSetCarrierOffset(Carrier_Type carrier_type, bool *isValid)
    {
        (void) carrier_type;
        *isValid = false;
        return qMakePair(0, 0);
    }
    virtual void pluginGetCarrierOffset(Carrier_Type carrier_type, int delta_x, int delta_y)
    {
        (void) carrier_type;
        (void) delta_x;
        (void) delta_y;
    }
    virtual QColor pluginSetCarrierColor(Carrier_Type carrier_type, bool *isValid)
    {
        (void) carrier_type;
        *isValid = false;
        return QColor();
    }
    virtual void pluginGetCarrierColor(Carrier_Type carrier_type, QColor background_color)
    {
        (void) carrier_type;
        (void) background_color;
    }
    virtual int pluginSetCarrierRadius(Carrier_Type carrier_type, bool *isValid)
    {
        (void) carrier_type;
        *isValid = false;
        return 0;
    }
    virtual void pluginGetCarrierRadius(Carrier_Type carrier_type, int radius)
    {
        (void) carrier_type;
        (void) radius;
    }
    virtual QSize pluginSetCarrierSize(Carrier_Type carrier_type, bool *isValid)
    {
        (void) carrier_type;
        *isValid = false;
        return QSize();
    }
    virtual void pluginGetCarrierQMenu(Carrier_Type carrier_type, QMenu *menu, P_Sender * const action_sender)
    {
        (void) carrier_type;
        (void) menu;
        (void) action_sender;
    }
    virtual QPair<QMenu *, P_Sender * const> pluginAddToCarrierQMenu(Carrier_Type carrier_type, bool *isValid)
    {
        (void) carrier_type;
        *isValid = false;
        return QPair<QMenu *, P_Sender * const>(nullptr, nullptr);
    }
    virtual QSize pluginSetWidgetSize(Carrier_Type carrier_type, bool *isValid)
    {
        (void) carrier_type;
        *isValid = false;
        return QSize();
    }
    virtual QPoint pluginSetCarrierPos(Carrier_Type carrier_type, QPoint item_pos, QSize item_size, bool *isValid)
    {
        (void) carrier_type;
        (void) item_pos;
        (void) item_size;
        *isValid = false;
        return QPoint();
    }
    virtual int pluginSetCarrierPage(Carrier_Type carrier_type, int total_page, bool *isValid)
    {
        (void) carrier_type;
        (void) total_page;
        *isValid = false;
        return 0;
    }
    virtual void pluginGetIsMouseInPluginCarrier(Carrier_Type carrier_type, bool result)//用于给music-island打补丁
    {
        (void) carrier_type;
        (void) result;
    }
    virtual void pluginGetShowCarrierCloseButton(Carrier_Type carrier_type, bool result)
    {
        (void) carrier_type;
        (void) result;
    }
    virtual bool pluginSetShowCarrierCloseButton(Carrier_Type carrier_type, bool *isValid)
    {
        (void) carrier_type;
        *isValid = false;
        return false;
    }
    //for Easy_Desktop 0.0.1
    //不会修改PluginProxyInterface,无法控制插件怎么调用,只能控制Easy_Desktop怎么调用,至于插件主动更新,用P_Sender

protected:
    ///
    /// \brief m_proxyInter
    /// NEVER delete this object.
    ///
    PluginProxyInterface *m_proxyInter = nullptr;
};

QT_BEGIN_NAMESPACE

#define ModuleInterface_iid "com.deepin.dock.PluginsItemInterface"

Q_DECLARE_INTERFACE(PluginsItemInterface, ModuleInterface_iid)
QT_END_NAMESPACE

#endif // PLUGINSITEMINTERFACE_H
