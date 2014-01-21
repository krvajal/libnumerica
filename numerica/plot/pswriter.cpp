#include "pswriter.h"
#include<stdexcept>

using namespace std;
using namespace numerica::tools;

string PSWriter::path="/usr/bin/evince";


PSWriter::PSWriter(string filename)
    :f(filename.c_str()),name(filename),tjCmd("")
{
    if (!f.is_open())
        throw runtime_error("PSWriter:: can't open file");
    f<<"%!"<<endl;
    SetFont("Arial",12);
    SetLineWidth(0.5);
}

PSWriter::~PSWriter()
{
    Close();
}

void PSWriter::Close()
{
    f<<"showpage"<<endl;
    if (f.is_open()) f.close();
    string cmd=name;
    ifstream psviewer(path.c_str());
    if (psviewer.is_open())
        cmd=path+" "+name;
    if (system((string("open ")+name).c_str() ))
            cerr<<"PSWriter::Close(): System command failed\n";
}


void PSWriter::SetFont(string fontName, double size)
{
    f<<"/"<<fontName<<" findfont "<<size<<" scalefont setfont"<<endl;
}


void PSWriter::SetLineWidth(double width)
{
    f<<width<<" setlinewidth"<<endl;
}

void PSWriter::SetColor(RGBColor col)
{
    f<<col.r<<" "<<col.g<<" "<<col.b<<" setrgbcolor"<<endl;
}

void PSWriter::SetDashedLine(string pattern)
{
    f<<"["<<pattern<<"] 0 setdash"<<endl;
}

void PSWriter::SetSolidLine()
{
    SetDashedLine("");
}

void PSWriter::SetTextJustification(TextJustification j)
{
    static string cmds[]={"",
                          "dup stringwidth pop 2 div neg 0 rmoveto ",
                          "dup stringwidth pop neg 0 rmoveto "};
    tjCmd=cmds[j];
}



void PSWriter::DrawText(double x, double y, string text,double angle)
{
    f<<"gsave "<<x<<" "<<y<<" translate ";
    f<<angle<<" rotate 0 0 moveto ("<<text<<") ";
    f<<tjCmd;
    f<<"show grestore"<<endl;
}

void PSWriter::DrawSymbol(double x, double y, int num, double size)
{
    static string smbCmd=" gsave /ZapfDingbats findfont exch scalefont setfont moveto show grestore";
    f<<"(\\"<<num<<") ";
    f<<x-0.40*size<<" ";
    f<<y-0.34*size<<" ";
    f<<size<<smbCmd<<endl;
}


void PSWriter::DrawLine(double x1, double y1, double x2, double y2)
{
    f<<"newpath "<<x1<<" "<<y1;
    f<<" moveto "<<x2<<" "<<y2;
    f<<" lineto stroke"<<endl;
}

void PSWriter::DrawConnectedLine(const NVector& xs, const NVector& ys, bool closed)
{
    f<<"newpath "<<xs[0]<<" "<<ys[0]<<" moveto"<<endl;
    for (size_t i=1;i<xs.size();i++)
        f<<xs[i]<<" "<<ys[i]<<" lineto"<<endl;
    if (closed) f<<"closepath "<<endl;
    f<<"stroke"<<endl;
}

