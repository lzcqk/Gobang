# Gobang
Gobang with C++ and Opencv<br>
此代码满足15 X 15 五子棋棋盘 <br>
可以实现PVP和PVE两种游戏模式<br>

## 基本功能
i.游戏模式的选择（PVP，PVE）<br>
ii.选择是否先手<br>
iii.选择棋子颜色<br>
iiii.支持悔棋和撤销悔棋操作<br>
iiiii.读入旧棋盘操作<br>

### 涉及算法
棋局在电脑看来，就是一个15 X 15 的board数组，在其中，0代表空（未有棋子），PVE：1代表AI，2代表玩家；PVP：1代表玩家A，2代表玩家B<br>
当棋盘上某位置落下一个棋子时，board数组相应位置便会被赋予相应的值<br>

AI的落子选择主要应用极大极小值算法实现。<br>
所谓极大极小值便是，AI对棋局15 X 15 所有位置进行遍历，模拟在该处落子，根据所达成的结果在一个scoreboard数组相应位置加上不同的数值<br>
eg：AI模拟在一个位置模拟落子后，发现落下后达成活四的情况，则给socreboard数组对应落子位赋予一个值，例如1000<br>
  后继续模拟另一个位置，发现落下后达成死四的情况，则也给socreboard数组对应落子位赋予一个值，例如600（因为活四优于死四，故他的值要小于活四）<br>
在完成每个位置的模拟后，便要遍历scoreboard，找出最大得分的那个位置，后确定为真正的落子位<br>

当然，光有上面的一次模拟是远远不够的，你的人工智能由于目光短浅因此会变成人工智障<br>
所以，我们要做的便是，加大模拟次数（即模拟后续的棋盘发展），顺便模拟一下玩家的落子位，尽量让走的一步成为既是AI最优落子位，也是玩家最优落子位，做到优势占尽的目的<br>

当我们实现了多次模拟后，我们会发现，程序的运行效率下降了<br>
因为我们多次无意义的遍历，拖垮的程序，所以我们此时要应用ab剪枝（将无意义的遍历操作删除）<br>
我们会发现AI模拟落子位置时，其实只需要模拟在有棋子分布的部分那边，而不是模拟远离棋子的角落里面<br>
有了这个想法，我们便可以加入4个全局变量，分别记录最大最小的x，y<br>
现在我们知道了棋子的分布都在最大最小x，y的那个矩形里面<br>
那么，在模拟时，我们就将它向外扩大一圈，作为模拟范围，此时我们的模拟复杂度就大大降低了<br>

### 缺陷
当前的用户界面还不是非常良好，主要应用opencv提供的各种绘图函数实现<br>
这也就导致用户界面较为粗糙<br>
将来打算使用Qt做界面，同时加大AI的深度，以此通过用户体验<br>

