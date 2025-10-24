
#include <catui/sys/application.h>


using cat::ui::color;




auto main(int argc, char** argv, char** env) -> int
{
    if (argc>1)
    {
        cat::application app{"catui_test", cat::string::make_view_list(argc,argv,1)};
        app.set_global_theme("C64");
        return static_cast<int>(app.run());
    }

    cat::application app{"catui_test", {}};
    return static_cast<int>(app.run());
}
