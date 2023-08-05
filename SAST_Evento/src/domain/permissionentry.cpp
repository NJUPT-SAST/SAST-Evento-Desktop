#include "permissionentry.h"

PermissionEntry::PermissionEntry(QString permissionId,
                                 QString event,
                                 QVector<QString> methodAllowed)
    : m_permissionId(std::move(permissionId)),
      m_event(std::move(event)),
      m_methodAllowed(std::move(methodAllowed))
{}
