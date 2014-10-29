#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <cstdio>
#include <cmath>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

void gnuplot(const vector<double>& x)
{
    const char fileName[] = "data";
    FILE* fp = fopen(fileName, "w+");
    for (int i = 0; i < x.size(); ++i)
    {
        fprintf(fp, "%g %g\n", x[i], double(i)/x.size());
    }
    fclose(fp);
    fp = popen("gnuplot", "w");
    fprintf(fp, "plot \'%s\' smooth unique\n", fileName);
    fprintf(fp, "pause -1\n");
    fflush(fp);
    pclose(fp);
}

int main()
{
  unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  uniform_real_distribution<double> distribution(0.0, 1.0);
  vector<double> x(10000);

  x[0] = distribution(generator);
  auto P = [](double x) {return x*(1-x);};
  for (int i = 1; i < x.size(); ++i)
  {
      x[i] = distribution(generator);
      if (P(x[i]) < P(x[i-1])*distribution(generator))
        x[i] = x[i-1];
  }
  std::sort(x.begin(), x.end());
  gnuplot(x);
  return 0;
}
