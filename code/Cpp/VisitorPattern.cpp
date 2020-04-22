#include <iostream>
#include <string>
#include <algorithm> //to use for_each();
#include <sstream>

using namespace std;

/*in the visitor pattern, we have to modify the
 hierarchy, but only once, and we define a code that
 allows to visit the elements in a hierarchy */

//forward declarations
struct Element;
struct TextElement;
struct Paragraph;
struct ListItem;
struct List;

struct Visitor
 {
    virtual ~Visitor() = default;
    virtual void visit(const Paragraph& p) = 0;
    virtual void visit(const ListItem&e) = 0;
    virtual void visit(const List&e) = 0;
    virtual std::string str()const = 0;
 };

struct Element
{
    virtual ~Element() = default;
	virtual void accept(Visitor& v) const = 0;
};

struct TextElement : Element
{
	std::string text;

    explicit TextElement(const std::string& text):text(text)
    {
    }
};

struct Paragraph :TextElement
{
	explicit Paragraph(const std::string& text): TextElement(text)
	{
	}
    void accept(Visitor& v) const override
    {
        v.visit(*this);
    }
};

struct ListItem : TextElement
{
    ListItem(const std::string& text) : TextElement(text)
	{
	}

    void accept(Visitor& v) const override
    {
        v.visit(*this);
    }
};

struct List : std::vector<ListItem>, Element
{
	List(const ::std::initializer_list<value_type>& Ilist) : vector<ListItem>(Ilist)
	{
	}

    void accept(Visitor& v) const override
    {
        v.visit(*this);
    }
};


struct HtmlVisitor: Visitor
{
    void visit(const Paragraph& p) override
    {
        oss << "<p>" << p.text << "</p>\n";
    }

    void visit(const ListItem& p) override
    {
        oss << "<li>" << p.text << "</li>\n";
    }

    void visit(const List& p) override
    {
        oss << "<ul>";
        for(auto x: p )
        {
            x.accept(*this);
        }
        oss  << "</ul>\n";
    }

    std::string str() const override
    {
        return oss.str();
    }
private:
    ostringstream oss;
};

struct MarkdownVisitor: Visitor
{
    void visit(const Paragraph& p) override
    {
        oss << "\n" << p.text << "\n";
    }

    void visit(const ListItem& p) override
    {
        oss << " -" << p.text << "\n";
    }

    void visit(const List& p) override
    {
        oss << '\n';
        for(auto x: p )
        {
            x.accept(*this);
        }
        oss << '\n';
    }

    std::string str() const override
    {
        return oss.str();
    }
private:
    ostringstream oss;
};

int main()
{
    cout << "Visitor Pattern!" << endl;

    Paragraph p{"Some colors: "};
    ListItem red  {"red"};
    ListItem blue {"blue"};
    ListItem green{"green"};
    List colors{ red, blue, green};
    vector<Element*> document {&p, &colors};

    HtmlVisitor v;

    cout << "Html" << endl;

    for(auto x: document)
    {
        x->accept(v);
    }
    cout << v.str() << endl;

    cout << "Markdonw:" << endl;

    MarkdownVisitor md;
    for(auto x: document)
    {
        x->accept(md);
    }
    cout << md.str() << endl;

    getchar();
    return 0;
}
