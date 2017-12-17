#ifndef GITEMFACTORY_H
#define GITEMFACTORY_H
#include <iostream>
#include <string>
#include <map>

enum GItemType
{
    kItemType_Invalid,
    kItemType_ActivityMsgItem,
    kItemType_FriendMsgItem,
    kItemType_AdItem
};

class GBaseItem
{
public:
    virtual ~GBaseItem(){}
    virtual void PrintType() = 0;
};

class GActivityMsgItem:public GBaseItem
{
public:
    static GActivityMsgItem* CreateWithFile(const std::string& filePath)
    {
        std::cout << "Readfile(" << filePath << ") to create GActivityMsgItem" << std::endl;
        return (new GActivityMsgItem());
    }

    void PrintType()
    {
        std::cout << "GActivityMsgItem" << std::endl;
    }
};

class GFriendMsgItem:public GBaseItem
{
public:
    static GFriendMsgItem* CreateWithFile(const std::string& filePath)
    {
        std::cout << "Readfile(" << filePath << ") to create GFriendMsgItem" << std::endl;
        return (new GFriendMsgItem());
    }

    void PrintType()
    {
        std::cout << "GFriendMsgItem" << std::endl;
    }
};

class GAdItem:public GBaseItem
{
public:
    static GAdItem* CreateWithFile(const std::string& filePath)
    {
        std::cout << "Readfile(" << filePath << ") to create GAdItem" << std::endl;
        return (new GAdItem());
    }

    void PrintType()
    {
        std::cout << "GAdItem" << std::endl;
    }
};

class GItemFactory
{
public:
    static GItemFactory* GetInstance()
    {
        static GItemFactory* item_factory = NULL;
        if(!item_factory)
        {
            item_factory = new GItemFactory();
            item_factory->InitItemFactory();
        }
        return item_factory;
    }

    GBaseItem* CreateItem(GItemType item_type)
    {
        GBaseItem* temp = NULL;
        switch (item_type)
        {
        case kItemType_ActivityMsgItem:
        {
            temp = GActivityMsgItem::CreateWithFile(GetItemConfig(kItemType_ActivityMsgItem));
            break;
        }
        case kItemType_FriendMsgItem:
        {
            temp = GFriendMsgItem::CreateWithFile(GetItemConfig(kItemType_FriendMsgItem));
            break;
        }
        case kItemType_AdItem:
        {
            temp = GAdItem::CreateWithFile(GetItemConfig(kItemType_AdItem));
            break;
        }
        default:
            break;
        }
        return temp;
    }

private:
    void InitItemFactory()
    {
        RegistItem(kItemType_ActivityMsgItem,"path-ActivityMsgItem");
        RegistItem(kItemType_AdItem,"path-AdItem");
        RegistItem(kItemType_FriendMsgItem,"path-FriendMsgItem");
    }
    void RegistItem(GItemType item_type,const std::string& config)
    {
        item_config_map_.insert(std::make_pair(item_type,config));
    }
    const std::string& GetItemConfig(GItemType item_type)
    {
        std::map<GItemType,std::string>::iterator iter = item_config_map_.find(item_type);
        if(iter != item_config_map_.end())
        {
            return (iter->second);
        }
        return "";
    }

    std::map<GItemType,std::string> item_config_map_;
};

#endif // GITEMFACTORY_H
