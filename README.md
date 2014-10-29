如何产生给定密度函数的随机数呢？

原理很简单，先产生[0,1]的随机数的生成器：

  unsigned int seed = chrono::system_clock::now().time_since_epoch().count();//设一个时间种子
  
  default_random_engine generator(seed);//残生随机数生成器
  
  uniform_real_distribution<double> distribution(0.0, 1.0);//定义分布[0,1]的均匀分布
  
然后产生一个随机数:

  x[0] = distribution(generator);
  
定义一个概率分布密度函数，我们把它叫做P：

  auto P = [](double x) {return x*(1-x);};
  
数组你懂的：

  vector<double> x(10000);
  
循环开始，注意第一个数先放着不管：

  for (int i = 1; i < x.size(); ++i){
  
      x[i] = distribution(generator);//生成随机数
      
      if (P(x[i]) < P(x[i-1])*distribution(generator))//就是这样一种判断方法，这个过程中还需要一个随机数
      
        x[i] = x[i-1];//如果中了这个判断，那么就让这个数和上一个数一样
        
  }
  
然后你就得到了一组以P为密度函数的随机数了，是不是很方便。

你还可以排个序。

  std::sort(x.begin(), x.end());
  
好了祝大家玩得开心。
