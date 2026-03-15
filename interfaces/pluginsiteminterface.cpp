// SPDX-FileCopyrightText: 2026 github.com:3084793958
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "pluginsiteminterface.h"

P_Version::P_Version(uint m_Major_Version, uint m_Minor_Version, uint m_Patch_Version)
{
    Major_Version = m_Major_Version;
    Minor_Version = m_Minor_Version;
    Patch_Version = m_Patch_Version;
}
bool P_Version::operator==(P_Version m_version) const
{
    return Major_Version == m_version.Major_Version && Minor_Version == m_version.Minor_Version && Patch_Version == m_version.Patch_Version;
}
bool P_Version::operator!=(P_Version m_version) const
{
    return !(operator==(m_version));
}
bool P_Version::operator>(P_Version m_version) const
{
    if (Major_Version > m_version.Major_Version)
    {
        return true;
    }
    else if (Major_Version == m_version.Major_Version)
    {
        if (Minor_Version > m_version.Minor_Version)
        {
            return true;
        }
        else if (Minor_Version == m_version.Minor_Version)
        {
            if (Patch_Version > m_version.Patch_Version)
            {
                return true;
            }
        }
    }
    return false;
}
bool P_Version::operator>=(P_Version m_version) const
{
    return (*this > m_version) || (*this == m_version);
}
bool P_Version::operator<(P_Version m_version) const
{
    return ! (*this >= m_version);
}
bool P_Version::operator<=(P_Version m_version) const
{
    return ! (*this > m_version);
}
QString P_Version::VersionName() const
{
    return QString("%1.%2.%3").arg(Major_Version).arg(Minor_Version).arg(Patch_Version);
}
P_Sender::P_Sender(QObject *parent, bool m_allow_Send_Data, bool m_allow_Send_Ptr)
    :QObject(parent)
    ,allow_Send_Data(m_allow_Send_Data)
    ,allow_Send_Ptr(m_allow_Send_Ptr)
{
    //对于Q_OBJECT,必须分出一个.cpp文件
}
void P_Sender::Send()
{
    emit sig_Send();
}
void P_Sender::Send_Data(QVariant var)
{
    if (allow_Send_Data)
    {
        emit sig_Send_Data(var);
    }
    else
    {
        Send();
    }
}
void P_Sender::Send_Ptr(void *ptr)
{
    if (allow_Send_Ptr)
    {
        emit sig_Send_Ptr(ptr);
    }
    else
    {
        Send();
    }
}
