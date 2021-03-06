#include "core/info.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "core/ising.h"

using namespace std;

ISING_TOOLKIT_NAMESPACE_BEGIN

string InformationSeparator()
{
    const size_t kInformationSeparatorLength = 60;
    const char   kInformationSeparatorSymbol = '*';

    string s;
    for (int i = 0; i != kInformationSeparatorLength; ++i)
        s += kInformationSeparatorSymbol;
    return s;
}

void PrintProgress(const size_t & total, const size_t & progress)
{
    const size_t     kProgressBarWidth = 40;
#ifndef ISING_PARALLEL
    const streamsize kPrecision        = 2;
    const streamsize kDefaultPrecision = cerr.precision();
    size_t width = kProgressBarWidth * progress / total;
    // Progress bar.
    cerr << "[" << string(width, '=') << ">" << string(kProgressBarWidth - width, ' ') << "]";
    // Percentage.
    cerr << setw(5 + kPrecision) << setprecision(kPrecision) << fixed
         << 100.0 * progress / total
         << "%\r"
         << skipws << setprecision(kDefaultPrecision) << defaultfloat;
    cerr.flush();
#else
    if (total < kProgressBarWidth)
        cerr << "=";
    else
        if ((progress + 1) % (total / kProgressBarWidth) == 0)
            cerr << "=";
#endif
}

ISING_TOOLKIT_NAMESPACE_END
