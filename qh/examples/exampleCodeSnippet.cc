#include <cc/ui/Application>
#include <cc/ui/Row>
#include <cc/ui/StylePlugin>
#include <cc/ui/Label>
#include <qh/CodeSnippet>

using namespace cc;
using namespace cc::ui;
using namespace qh;

class MainView: public View
{
    friend class Object;

    MainView()
    {
        size = Size{640, 480};
        color = Color{"#FFFFFF"};

        Row *box = Row::create(this);
        box->color = Color{"#F0F0F0"};
        box->centerInParent();

        CodeSnippet::create(box,
            "int main(int argc, char **argv)\n"
            "{\n"
            "   printf(\"Hello, world!\\n\");\n"
            "   return 0;\n"
            "}"
        );

        keyPressed->connect([=]{
            if (+(key()->modifiers() & KeyModifier::Control)) {
                if (key()->keyCode() == '+') {
                    Application::instance()->textZoom += 4;
                }
                else if (key()->keyCode() == '-') {
                    Application::instance()->textZoom -= 4;
                }
            }
        });
    }
};

int main(int argc, char **argv)
{
    Application *app = Application::open(argc, argv);
    // app->textZoom = 20;
    Window::open(Object::create<MainView>(), "Hello, world!");
    return app->run();
}
