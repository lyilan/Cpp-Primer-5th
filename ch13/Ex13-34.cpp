#include <string>
#include <set>

class Folder;
class Message;

class Message
{
    friend class Folder;
    friend void swap(Message &, Message &);

public:
    // folders 被隐式初始化为空集合
    explicit Message(const std::string &str = "") : contents(str) {}
    // 拷贝控制成员，管理指向本Message的指针
    Message(const Message &);            // 拷贝构造函数
    Message &operator=(const Message &); // 拷贝赋值运算
    ~Message();                          // 析构函数
    // 从给定的Folder集合中添加/删除本Message
    void save(Folder &);
    void remove(Folder &);
    // 为本Message在folders中添加/删除指定的Folder指针
    void addFolder(Folder *f) { folders.insert(f); }
    void remFolder(Folder *f) { folders.erase(f); }

private:
    std::string contents;       // 实际消息文本
    std::set<Folder *> folders; // 包含本Message的Folder的地址集合
    // 工具函数
    // 将本Message添加到指定Message的folders当中去
    void add_to_Folders(const Message &);
    // 从folders中的每个folder中删除本Message
    void remove_from_Folders();
};

class Folder
{
    friend class Message;

public:
    // 拷贝控制成员，管理指向本Folder的指针
    Folder(const Folder &);               // 拷贝构造函数
    Folder &operator=(const Folder &rhs); // 拷贝赋值运算符
    ~Folder();                            // 析构函数
    // 为本Folder在messages中添加/删除指定的message指针
    void addMsg(Message *m) { messages.insert(m); }
    void remMsg(Message *m) { messages.erase(m); }

private:
    std::set<Message *> messages;
    // 将本Folder添加到指定Folder的message当中去
    void add_to_Messages(const Folder &);
    // 从messages的每个message中删除本Folder
    void remove_from_Messages();
};

void Message::save(Folder &f)
{
    // 将给定的Folder插入到我们的Folders集合中
    folders.insert(&f);
    // 将本Message添加到f的Message集合中
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    // 将给定的Folder从我们的Folders集合中删除
    folders.erase(&f);
    // 将本Message从f的message结合中删除
    f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders)
    {
        f->addMsg(this);
    }
}

void Message::remove_from_Folders()
{
    for (auto f : folders) // 对folders中的每个指针
    {
        f->remMsg(this); // 从该Folder中删除本Message
    }
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

Message::~Message()
{
    remove_from_Folders();
}

Message &Message::operator=(const Message &rhs)
{
    // 先删除指针再插入他们来处理自赋值的情况
    remove_from_Folders();   // 更新已有的Folder
    contents = rhs.contents; // 从rhs拷贝消息内容
    folders = rhs.folders;   // 从rhs拷贝Folder指针
    add_to_Folders(rhs);     // 将本message添加到那些Folder中
    return *this;
}

void Folder::add_to_Messages(const Folder &f)
{
    for (auto m : f.messages)
        m->addFolder(this);
}

void Folder::remove_from_Messages()
{
    for (auto m : messages)
        m->remFolder(this);
}

Folder::Folder(const Folder &f) : messages(f.messages)
{
    add_to_Messages(f);
}

Folder &Folder::operator=(const Folder &rhs)
{
    remove_from_Messages();
    messages = rhs.messages;
    add_to_Messages(rhs);
    return *this;
}

Folder::~Folder()
{
    remove_from_Messages();
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

int main()
{
    return 0;
}