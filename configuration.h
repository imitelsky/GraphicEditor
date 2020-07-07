#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "configurationi.h"

struct node
{
	int mId;
	sPoint mBottomLeft;
	sPoint mTopRight;
	static node create(int iId, const sPoint& iFirst, const sPoint& iSecond)
	{
		node res;
		res.mId = iId;
		res.mBottomLeft = iFirst;
		res.mTopRight = iSecond;
		return res;
	}
};

class Configuration : public ConfigurationI
{
public:
    Configuration(std::string iFileName = "file.xml") : mFileName(iFileName) {}
	virtual void add(int iId, sPoint iFirst, sPoint iSecond) override;
	virtual void save() override;
	virtual void load(const PContainerI& iContainer) override;
private:
    std::string       mFileName;
	std::vector<node> mNodesToSave;
};

using PConfiguration = std::shared_ptr<Configuration>;
#endif
