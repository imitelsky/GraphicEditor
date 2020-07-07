#include "configuration.h"
#include "containeri.h"
#include "pugixml.hpp"

void Configuration::add(int iId, sPoint iFirst, sPoint iSecond)
{
	mNodesToSave.push_back(node::create(iId, iFirst, iSecond));
}

void Configuration::save()
{
	pugi::xml_document doc;

	auto declarationNode = doc.append_child(pugi::node_declaration);
	declarationNode.append_attribute("version") = "1.0";
	declarationNode.append_attribute("encoding") = "UTF-8";
	declarationNode.append_attribute("standalone") = "yes";

	auto root = doc.append_child("Root");

	for (auto node : mNodesToSave)
	{
		pugi::xml_node nodeChild;
		if (node.mId == eShapeId_Rectangle || node.mId == eShapeId_Triangle || node.mId == eShapeId_Ellipse)
        {
			nodeChild = root.append_child("Shape");
            nodeChild.append_attribute("shapeId").set_value(node.mId);
        }
		else if (node.mId == eShapeId_Line)
			nodeChild = root.append_child("Line");
		else
			continue;

		nodeChild.append_attribute("x1").set_value(node.mBottomLeft.x);
		nodeChild.append_attribute("y1").set_value(node.mBottomLeft.y);
		nodeChild.append_attribute("x2").set_value(node.mTopRight.x);
		nodeChild.append_attribute("y2").set_value(node.mTopRight.y);
	}

    doc.save_file(mFileName.c_str(), PUGIXML_TEXT("  "));

	mNodesToSave.clear();
}

void Configuration::load(const PContainerI& iContainer)
{
	pugi::xml_document doc;
    doc.load_file(mFileName.c_str());

    if (doc.empty())
        return;

	pugi::xml_node nodes = doc.child("Root");

    if (nodes.empty())
        return;

	iContainer->clear();

	for (pugi::xml_node fi = nodes.first_child(); fi; fi = fi.next_sibling())
	{
		std::string nodeName = fi.name();
		if ("Shape" == nodeName)
		{
			int id = fi.attribute("shapeId").as_int();
			int x1 = fi.attribute("x1").as_int();
			int y1 = fi.attribute("y1").as_int();
			int x2 = fi.attribute("x2").as_int();
			int y2 = fi.attribute("y2").as_int();
			iContainer->addShape(id, {x1, y1}, {x2, y2});
		}
		else if ("Line" == nodeName)
		{
			int x1 = fi.attribute("x1").as_int();
			int y1 = fi.attribute("y1").as_int();
			int x2 = fi.attribute("x2").as_int();
			int y2 = fi.attribute("y2").as_int();
			iContainer->addLine({ x1, y1 }, { x2, y2 });
		}
	}
}
