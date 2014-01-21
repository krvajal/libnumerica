#ifndef PSWRITER_H
#define PSWRITER_H

#include<valarray>
#include<string>
#include<fstream>

#include <numerica/tools/nvector.h>

namespace numerica
{
    namespace tools
    {
        using std::string;
        enum TextJustification{tjLeft,tjCentered,tjRight};

        struct RGBColor
        {
            constexpr RGBColor(double red=1,double green=0,double blue=1)
                :r(red),g(green),b(blue){}
            double r,g,b;
        };

        constexpr RGBColor Red(1,0,0);

        class PSWriter
        {
        public:
            PSWriter(string filename);
            ~PSWriter();
            void Close();

            void SetFont(string fontName, double size);
            void SetLineWidth(double width);
            void SetColor(RGBColor color);
            void SetDashedLine(string pattern="4 2");
            void SetSolidLine();
            void SetTextJustification(TextJustification j=tjLeft);

            void DrawText(double x, double y, string text,double rot=0.0);
            void DrawSymbol(double x, double y, int num=108, double size=12);
            void DrawLine(double x1, double y1, double x2, double y2);
            void DrawConnectedLine(const NVector& xs,const NVector& ys,bool closed=false);

            static string path;


        private:
            std::ofstream f;
            std::string name, tjCmd;
        };
    }
}



#endif // PSWRITER_H
