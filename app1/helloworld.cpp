// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include<queue>
#include<string>
#include<limits.h>

using namespace std;

template<typename T1, typename T2>
auto max(T1 a, T2 b) { return a>b ?a:b; }

template<typename T1, typename T2>
auto min(T1 a, T2 b) { return a>b ?b:a; }

unordered_map<int, int> out;

int maxGain(vector<int> price,int n) {
	if (n == 0) return 0;
	if (out.size() && out[n]) return out[n];
	int max_val = INT_MIN;
	for (int i=0;i<n;++i)
	{
		max_val = max(max_val, price[i] + maxGain(price, n - i-1));
	}
	out[n] = max_val;
	return max_val;
}

unordered_map<int,unordered_map<int,int>> kmap;
int knapsak(vector<int> price,vector<int> w,int i,int cap) {
	if (i > price.size()) {
		kmap[cap][i] = 0;
		return kmap[cap][i];
		}

	if(cap<w[i]) {
		if (kmap[cap][i+1]){
			return kmap[cap][i+1];
		} 
		return kmap[cap][i+1] = knapsak(price,w,i+1,cap);
	}
	
	if(cap>w[i]){
		if(!kmap[cap][i+1]){
			kmap[cap][i+1] = knapsak(price,w,i+1,cap);
		}

		if(!kmap[cap-w[i]][i+1]){
			kmap[cap-w[i]][i+1] = knapsak(price,w,i+1,cap-w[i]);
		}
		return max( kmap[cap][i+1],price[i]+kmap[cap-w[i]][i+1]);
	}
}

int count(int S[], int m, int n)
{
	// If n is 0 then there is 1 solution  
	// (do not include any coin) 
	if (n == 0)
		return 1;

	// If n is less than 0 then no  
	// solution exists 
	if (n < 0)
		return 0;

	// If there are no coins and n  
	// is greater than 0, then no 
	// solution exist 
	if (m <= 0 && n >= 1)
		return 0;

	// count is sum of solutions (i)  
	// including S[m-1] (ii) excluding S[m-1] 
	return count(S, m - 1, n) + count(S, m, n - S[m - 1]);
}

template<class T>
void myswap(T&a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}
void swapArray(vector<int>& arr) {
	int l = arr.size();
	for (int i = 0; i < l / 2; ++i) {
		myswap(arr[i], arr[l - i - 1]);
	}
}

int coinChange(int arr[],int m, int t) {
	int** v= new int*[m];

	for(int i=0;i<m;++i)
	{
		v[i] = new int[t+1];
	}

	for (int j = 0; j <m; ++j) {

		for (int k = 0; k < t + 1; k++) {
			if (arr[j] < t) {
				
				if (k == 0) {
					v[j][k] = 1;
					continue;
				}
				
				if (j == 0) {
					v[j][k] = 1;
				}
				else {
					if (arr[j] <= k) {
						v[j][k] = v[j - 1][k] + v[j][k - arr[j]];
					}
					else {
						v[j][k] = v[j - 1][k];
					}
					
				}
			}
			


		}
	}
	return v[m - 1][t];

}

int countSetUtil(int num) {
	int check = 1;
	int count = 0;
	while (num) {
		count += num & check;
		//check = check << 1;
		num = num >> 1;
	}

	return count;
}

int diff(int a, int b) {
	return a > b ? a - b : b - a;
}

int countSet(int num1, int num2) {
	return diff(countSetUtil(num1), countSetUtil(num2));
}

typedef struct  _tree
{
	int data;
	_tree*left;
	_tree*right;
	_tree(int val) {
		data = val;
		left = NULL;
		right = NULL;
	}
}Tree;

Tree* root;


void dfs(Tree* root) {
	if (root) {
		cout << root->data << ",";
		dfs(root->left);
		dfs(root->right);
	}
}

void bfs(Tree* root) {
	if (root) {
		queue<Tree*> bp;
		
		bp.push(root);
		//bp.push(root->right);
		while (!bp.empty()) {
			Tree* temp = bp.front();
			bp.pop();
			if (temp) {
				cout << temp->data << ",";
				if(temp->left) bp.push(temp->left);
				if(temp->right) bp.push(temp->right);
			}	
			
		}
		cout<<endl;

	}
}

void stringPermuation(string str,int b,int e) {
	if (b == e) {
		cout << str << endl;
		return;
	}
	for (int i = b; i < e; ++i) {
		myswap<char>(str[i], str[b]);
		stringPermuation(str, b + 1, e);
		myswap<char>(str[i], str[b]);
	}


}

/**/
void towerOfHanoi(int disc ,char src, char dest,char med) {

	
	if (disc == 1) {
		cout << "transfer disc :" << disc << " from " << src << " to " << dest << endl;
	return; 
	}

	towerOfHanoi(disc-1, src, med, dest);
	cout << "transfer disc :" << disc << " from " << src << " to " << dest << endl;
	towerOfHanoi(disc-1, med, dest, src);
}

int lcs(string s1,string s2){
	vector<vector<int>> table;

	int l1 = s1.size();
	int l2 = s2.size();
	// string subseq;

	for (int i = 0; i < l1+1; i++)
	{
		vector<int> temp;
		for (int j = 0; j < l2+1; j++)
		{
			temp.push_back(0);
		}
		table.push_back(temp);
		
	}
	int i,j;
	
	for (i = 1; i < l1+1; i++)
	{
		for (j = 1; j < l2+1; j++)
		{
			if(s1[i-1] == s2[j-1]){
			// subseq.push_back(s1[i-1]);
			table[i][j] = 1+table[i-1][j-1];
			}
			else{
				table[i][j] = max(table[i-1][j],table[i][j-1]);
			}			
		}
	}
	// cout<<subseq<<endl;
	return table[l1][l2];	
}

vector<vector<int>> table_lcs;
int lcs_recursive(string s1,string s2,int m,int n){
	if (m==0 || n==0) return 0;

	if(s1[m-1]==s2[n-1]){
		// if(table_lcs[m][n])
		return 1+lcs_recursive(s1,s2,m-1,n-1);
	}
	else
		return max(lcs_recursive(s1,s2,m-1,n),lcs_recursive(s1,s2,m,n-1));
}

void pattern_parse(string str,int* arr){
	arr[0]=0;
	for(int i=1,j=0 ;i<str.size();){
		if(str[i]==str[j]){
			++j;
			arr[i]=j;
			
			++i;
		}
		else{
			if(j>0){
				j=arr[j-1];
			}
			else{
				arr[i]=0;
				++i;
			}
			
		}
	}
}

int kmp_search(string str,string kmp){

	// string kmp("abcaby");
	int* arr1=new int(kmp.size());
	pattern_parse(kmp,arr1);
	int starting_index = -1;;
	int match_size =0;
	for(int i=0,j=0 ;i<str.size() && j<kmp.size();){
		if(str[i]==kmp[j]){
			++j;
			++i;
			match_size++;
		}
		else{
			
			if(j>0){
				j=arr1[j-1];
				
			}
			else{
				// match_size = 0;
				// arr1[i]=0;
				++i;
			}
			match_size = j;
			starting_index = i-j;
			
		}
	}
	cout<<"matchin index is : "<<starting_index<<endl;
	return match_size;
}
// int matrix_chain_mutiplication(pair<int,int>p1,pair<int,int>p2,pair<int,int>p3){


// }

int heightOFTree(Tree* root,int max){
	if(root==NULL) return 0;


}

int main()
{
	string str("abcxabcdabcdabcy");
	string patt("abcdabcy");
	cout<<"match pattern size is: "<<kmp_search(str,patt)<<endl;
	string s1="abcd";
	string s2="qahcgde";
	cout<<"longest common subsequence is of length: "<<lcs(s1,s2)<<endl;
	vector<int> v1 = { 9,  10 , 17,  15,  20 };
	vector<int> w = { 3,  4, 7,  6,  10 };
	cout<<"max output generate is :"<<knapsak(v1,w, 0,12)<<endl;

	towerOfHanoi(3, 'A', 'B', 'C');
	string s("ABC");
	stringPermuation(s, 0, 3);
	Tree* btree = new Tree(6);
	btree->left = new Tree(3);
	btree->right = new Tree(9);
	btree->left->left = new Tree(2);
	btree->left->right = new Tree(4);
	btree->right->left = new Tree(8);
	btree->right->right = new Tree(10);

	dfs(btree);
	cout << endl;
	bfs(btree);
	
	cout<<"bit diff:"<<countSet(14,7)<<endl;
	int i, j;
	int arr[] = { 1, 2, 3 };
	vector<int> sarr = { 1,2,3,4,5,5,6,7,8,9,100 };
	int m = sizeof(arr) / sizeof(arr[0]);
	swapArray(sarr);

	for(int i=0;i<sarr.size();++i)
	{
		cout << sarr[i] << "," << endl;
	}
	cout<<coinChange(arr, m, 5)<<endl;
	vector<int> v = { 1,5  , 8 ,  9,  10 , 17,  17,  20 };
	maxGain(v, 8);

}

