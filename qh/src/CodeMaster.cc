#include <cc/debug>
#include <cc/Singleton>
#include <cc/toki/Registry>
#include <qh/CodeMaster>

namespace qh {

const CodeMaster *CodeMaster::instance()
{
    return Singleton<CodeMaster>::instance();
}

CodeMaster::CodeMaster():
    theme_(toki::Theme::load("ClassicWhite"))
{
    {
        toki::Language *cxx = 0;
        toki::registry()->lookupLanguageByName("cxx", &cxx);
        language_ = cxx;
    }

    CC_INSPECT(theme_->path());
}

} // namespace qh
