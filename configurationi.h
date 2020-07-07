#ifndef CONFIGURATIONI_H
#define CONFIGURATIONI_H

#include "defines.h"

class ContainerI;
using PContainerI = std::shared_ptr<ContainerI>;

class ConfigurationI
{
public:
    virtual ~ConfigurationI() {}
	virtual void add(int iId, sPoint iFirst, sPoint iSecond) = 0;
	virtual void save() = 0;
	virtual void load(const PContainerI& iContainer) = 0;
};

using PConfigurationI = std::shared_ptr<ConfigurationI>;

#endif
