#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;



int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n;
	fin >> n;
	string helpius;
	getline(fin, helpius);

	vector<int> order;
	vector<bool> visited(1 + n, false);
	vector<vector<int>> in(1 + n);
	vector<vector<int>> from(1 + n);
	vector<int> dol(1 + n,0);
	/*string temp;
	string str;
	int begPos = 0;
	bool haveSpace = false;
	for (int a = 1; a < n + 1; a++) 
	{
		getline(fin, str);
		for (int i = 0; i < str.size(); i++) 
		{
			if (str[i] == ' ')
			{
				for (int j = 0, k = begPos; k < i; k++,j++)
				{
					temp[j] = str[k];
					
				}
				if (std::atoi(temp.c_str()) != 0)
				{
					from[a].push_back(std::atoi(temp.c_str()));
				}
				begPos = i + 1;
			}
			if (i == str.size() - 1)
			{
				for (int j = 0,k = begPos; k < str.size(); j++,k++)
				{
					temp[j] = str[k];
				}
				if (std::atoi(temp.c_str()) != 0)
				{
					from[a].push_back(std::atoi(temp.c_str()));
				}
			}
			for (int h = 0; h < temp.size(); h++)
			{
				temp[h] = NULL;
			}
			
			
		}
		
		begPos = 0;
	}
	*/
	string str;
	int v;
	for (int i = 1; i < n + 1; i++)
	{
		getline(fin, str);
		istringstream is(str);
		while (is >> v)
		{
			if (v == 0)
			{
				break;
			}
			else
			{
				from[i].push_back(v);
			}
		}
	}
	function<void(int)> DoDFS = [&](int v)
	{
		//fout << "rfrfrf" << endl;
		if (visited[v])
		{
			return;
		}
		//fout << v << endl;
		visited[v] = true;
		for (int child : from[v])
		{
			//fout << "freferfref" << " ";

			DoDFS(child);
		}
		order.push_back(v);
	};
	int count = 0;
	for (int v = 1; v < n + 1; v++)
	{
		if (!visited[v])
		{
			count++;
			DoDFS(v);
		}
	}
	vector<int> id(1 + n, 0);
	int nowid = 0;
	function<void(int)> SetId = [&](int v)
	{
		if (id[v] != 0)
		{
			return;
		}
		id[v] = nowid;
		for (int child : from[v])
		{
			SetId(child);
		}
	};
	for (int i = order.size() - 1; i >= 0; i--)
	{
		int v = order[i];
		if (id[v] == 0)
		{
			nowid++;
			SetId(v);
		}
	}
	for (int i = 1; i < visited.size();i++)
	{
		visited[i] = 0;
	}
	int D1 = 0;
	int D2 = 0;
	bool ISD = true;
	function<void(int)> DoBFS = [&](int v)
	{
		if (!visited[v])
		{
			for (int child : from[v])
			{
				visited[v] = true;
				if (dol[v] == 1)
				{
					dol[child] = 2;
				}
				else
				{
					dol[child] = 1;
				}
				DoBFS(child);
			}
		}
		else
		{
			for (int child : from[v])
			{
				if (dol[v] == dol[child])
				{
					ISD = false;
				}
			}
			return;
		}
	};
	
	int indexsearch = nowid;
	int sum = 0;
	if (indexsearch == 1)
	{
		dol[1] = 1;
		DoBFS(1);
		for (int i = 1; i < n + 1; i++)
		{
			if (dol[i] == 1)
			{
				D1++;
			}
			if (dol[i] == 2)
			{
				D2++;
			}
		}
		if (ISD == 0)
		{
			fout << "YES";
		}
		else
		{
			fout << "NO" << endl;
			fout << max(D1, D2);
		}
	}
	else
	{
		fout << "NO" << endl;
		
		for (int i = 1; i < id.size(); i++)
		{
			if (id[i] == indexsearch && indexsearch != 0)
			{
				dol[i] = 1;
				DoBFS(i);
				indexsearch--;
				for (int i = 1; i < n + 1; i++)
				{
					//fout << dol[i] << " ";
					if (dol[i] == 1)
					{
						D1++;
						//fout <<"d1" << D1;
					}
					if (dol[i] == 2)
					{
						D2++;
					//	fout << D2;
					}
				}
				if (ISD == 1)
				{
					//fout << D1 << " " << D2 << endl;
					//fout << max(D1, D2) << endl;
					sum += max(D1, D2);
					
				}
				else
				{
					//fout << sum << endl;
					sum++;
					
				}
				for (int i = 1; i < n + 1; i++)
				{
					dol[i] = 0;
					D1 = 0;
					D2 = 0;
				}

			}

		}
		fout << sum;
	}
	
	
	return 0;
}