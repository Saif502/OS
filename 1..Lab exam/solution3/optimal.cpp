#include <iostream>
#include<vector>
using namespace std;

int predictPage(int page[], vector<int> &frames, int pageNumber, int pageIndex)
{
   int result = -1, farthestPage = pageIndex;
   for (int i = 0; i < frames.size(); i++)
   {
      int j;
      for (j = pageIndex; j < pageNumber; j++)
      {
         if (frames[i] == page[j])
         {
            if (j > farthestPage)
            {
               farthestPage = j;
               result = i;
            }
            break;
         }
      }

      if (j == pageNumber)
         return i;
   }

   if (result == -1)
      return 0;
   else
      return result;
}
bool searchPage(int key, vector<int> &frames)
{
   for (int i = 0; i < frames.size(); i++)
   {

      if (frames[i] == key)
         return true;
   }

   return false;
}
void find(int g[], int m, int s)
{
   vector<int> fra;
   int h = 0;
   for (int i = 0; i < m; i++)
   {
      if (searchPage(g[i], fra))
      {

         h++;
         continue;
      }

      if (fra.size() < s)
         fra.push_back(g[i]);
      else
      {
         int j = predictPage(g, fra, m, i + 1);
         fra[j] = g[i];
      }
   }
   if(m - h == 9) cout << "The no of Page Fault: " << m - h << ' ' <<  "\nFrame Number is " << s << endl;
}

int main()
{

   freopen("input.txt","r",stdin);

   int m, n;
   cin>> m >> n;

   int g[n];
   for(int i = 0; i < n; i++)
   {
       cin>>g[i];
   }

   for(int i = 2; i <= m; i++){
      find(g, n, i);
   }

   return 0;
}
