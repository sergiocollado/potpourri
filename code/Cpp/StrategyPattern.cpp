#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

enum class OutputFormat
{
   Html,
   Markdown
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void start(ostringstream& oss) = 0;
    virtual void end(ostringstream& oss) = 0;
    virtual void add_list_item(ostringstream& oss, const string& item) = 0;

};

struct MarkdownListsStrategy : ListStrategy
{
    void start(ostringstream& oss) override {}
    void end(ostringstream& oss) override {}
    void add_list_item(ostringstream& oss, const string& item) override
    {
        oss << " *" << item << "\n";
    }
};

struct HtmlListsStrategy : ListStrategy
{
    void start(ostringstream& oss) override
     {
         oss << "<ul>" << '\n';
     }
    void end(ostringstream& oss) override
    {
       oss << "</ul>" << '\n';
    }
    void add_list_item(ostringstream& oss, const string& item) override
    {
        oss << "<li>" << item << "</li>\n";
    }
};
struct TextProcessor
{
    void append_list(const vector<string> items)
    {
        list_stragety->start(oss);
        for (auto& item: items)
        {
            list_stragety->add_list_item(oss, item);
        }
        list_stragety->end(oss);
    }
    void clear()
    {
        oss.str("");
        oss.clear();
    }
    string str() const { return oss.str(); }
    void set_output_format(OutputFormat format)
    {
        switch(format)
        {
            case OutputFormat::Markdown:
                list_stragety = make_unique<MarkdownListsStrategy>();
                 break;
            case OutputFormat::Html:
                list_stragety = make_unique<HtmlListsStrategy>();
                 break;
            default:                    break;
        }
    }
private:
    ostringstream oss;
    unique_ptr<ListStrategy> list_stragety;
};


int main()
{
    cout << "Strategy Pattern!\n\n" << endl;

    TextProcessor tp;
    tp.set_output_format(OutputFormat::Markdown);
    tp.append_list({"one", "two", "three"});
    cout << tp.str() << '\n';

    tp.clear();
    tp.set_output_format(OutputFormat::Html);
    tp.append_list({"uno", "dos", "tres"});
    cout << tp.str() << '\n';

    getchar();
    return 0;
}
