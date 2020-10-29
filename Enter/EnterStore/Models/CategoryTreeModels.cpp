#include "pch.h"
#include "CategoryTreeModels.h"

using namespace EnterStore::Models;

CategoryTreeModels::CategoryTreeModels(int id,
	String^ parentId,
	bool isFurniture,
	String^ name,
	String^ token,
	String^ mediaImage,
	unsigned int level,
	String^ seoHeader,
	String^ productCount,
	String^ productCountGlobal,
	bool hasChildren)

	: tree_id(id), tree_parentId(parentId), tree_isFurniture(isFurniture),
	tree_name(name), tree_token(token), tree_mediaImage(mediaImage), tree_level(level),
	tree_seoHeader(seoHeader), tree_productCount(productCount), tree_productCountGlobal(productCountGlobal),
	tree_hasChildren(hasChildren)
{
}

int CategoryTreeModels::Id::get()
{
	return tree_id;
}

String^ CategoryTreeModels::ParentId::get()
{
	return tree_parentId;
}

bool CategoryTreeModels::IsFurniture::get()
{
	return tree_isFurniture;
}

String^ CategoryTreeModels::Name::get()
{
	return tree_name;
}

String^ CategoryTreeModels::Token::get()
{
	return tree_token;
}

String^ CategoryTreeModels::MediaImage::get()
{
	return tree_mediaImage;
}

unsigned int CategoryTreeModels::Level::get()
{
	return tree_level;
}

String^ CategoryTreeModels::SeoHeader::get()
{
	return tree_seoHeader;
}

String^ CategoryTreeModels::ProductCount::get()
{
	return tree_productCount;
}

String^ CategoryTreeModels::ProductCountGlobal::get()
{
	return tree_productCountGlobal;
}

bool CategoryTreeModels::HasChildren::get()
{
	return tree_hasChildren;
}

IVector<CategoryTreeModels^> ^ CategoryTreeModels::Children::get()
{
	return tree_children;
}

void CategoryTreeModels::Children::set(IVector<CategoryTreeModels^>^ val)
{
	tree_children = val;
}