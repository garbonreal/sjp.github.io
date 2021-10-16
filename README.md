# BFS-for-Black-Nodes
为解决在大规模图上找每个结点二阶邻居内异常点耗时过长的问题，尝试剪枝等优化算法

* BFS 是最基本的方法，分别对每个点进行深度为2的BFS遍历。预估的算法复杂度为 O(d* d* n)。(d 为每个结点的平均度数)
* heapBFS 是用堆将每个顶点的一阶黑点按序存储。如果要求结点 i 二阶邻居内的黑点数，可以用一个堆合并 i 所有一阶点的有序黑点，预估的算法复杂度为 O(log(d)* d* n)

在 snap 上选取了四张结点数从 10^3 到 10^5 的图，随机将图中的部分顶点设置为异常点(5% ~ 40%)，实验得到的数据如下(time unit: x 10-8 s): 
### facebook_combined, node=4039, edge=88234
|Black%|BFS|heapBFS|
| :----: | :--------: | :--------: |
|5%|10287856|11683402
|10%|9912179|34124908
|15%|10159106|68309399
|20%|10254473|102160372
|25%|10199581|135167551
|30%|9879567|162344097
|35%|9904005|186487551
|40%|9812588|202963757
---------------------------------------
### facebook_large, node=22470, edge=171002
|Black%|BFS|heapBFS|
| :----: | :--------: | :--------: |
|5%|	     13443515|	49750305
|10%|	     13512718|	74459548
|15%|	     13639217|	108434259
|20%|	     13646504|	148414232
|25%|	     13703182|	179959795
|30%|	     13625301|  207710285
|35%|	     13418233|	230697536
|40%|	     13440505|	236783672
---------------------------------------
### com-dblp, node=317080, edge=1049866
|Black%|BFS|heapBFS|
| :----: | :--------: | :--------: |
5%	     46335459	217672266
10%	     47665352	426885006
15%	     48713425	432771224
20%	     49167913	433336216
25%	     49136522	435738143
30%	     50769529	438009610
35%	     49442658	433954638
40%	     50016240	435056620
---------------------------------------
### github_developer, node=37700, edge=289003
|Black%|BFS|heapBFS|
| :----: | :--------: | :--------: |
5%	     113910099	166281120
10%	     117809481	518681932
15%	     124356087	989414796
20%	     123151094	1540421415
