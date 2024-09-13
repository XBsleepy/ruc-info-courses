辨析：

话题模型和词嵌入模型

tfidf

SVD分解

# 预习，启动！

## 建模与回归

### 建模的步骤：

1. 选择模型
2. 选择目标函数
3. 拟合模型：优化目标函数

### 线性回归

常数模型：

$y^ ̂=θ$

忽略了输入x

区别估计（estimation）和预测（prediction）：

* 估计是用观测的样本数据来拟合参数
* 预测是用拟合的参数来求解未知数据

损失函数（Loss Function）：

–度量模型预测的优劣，即真实值$y_i$与预测值$y ̂_i$之间的差异

–针对我们的常数模型，度量参数θ与真实观测值之间的误差

平方损失，又叫L2损失：

$L_2 (y_i,y ̂_i )=(y_i-y ̂_i )^2$

绝对损失，又叫L1损失：

$L_1 (y_i,y ̂_i )=|y_i-y ̂_i |$

•度量平均损失，也称经验风险（Empirical Risk）或目标函数（Objective Function）

$1/n ∑_{i=1}^nL(y_i,y ̂_i)$

优化参数的目标是最小化平均损失

**对于以平方损失为损失函数常数模型**

•几个结论：

–给定常数模型和均方误差，最优的参数估计是观测数据的均值

–给定均值作为估计，此时均方误差达到最小，等于观测数据的方差

–上述结论解释了为什么均值是重要的统 计变量

•注意：

–上述结论成立的条件：① 模型为常数；② 损失函数采用均方损失

**对于以平均绝对误差为损失函数的常数模型**

•几个结论：

–给定常数模型和平均绝对误差，最优参数估计是观测数据中位数

–给中位数作为估计，平均绝对误差达到最小

–此时的参数估计不容易受到离群点（Outlier）的影响

但当数据有偶数个时，实际上在中位数附近的两个值之间都不会影响绝对误差。

**Huber Loss：**

![image-20231209191413227](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209191413227.png)

以下是一些 $\alpha$ 参数的取值示例：

- 当数据集中异常值较少时，可以将 alpha 参数设置为较小的值，以便模型能够更好地学习到异常值。
- 当数据集中异常值较多时，可以将 alpha 参数设置为较大的值，以免模型过度学习到异常值。
- 当数据集中异常值的类型较为复杂时，可以将 alpha 参数设置为较大的值，以便模型能够更好地鲁棒性。

下面考虑$y ̂_i=a+bx_i$,该模型称为简单线性回归模型，简称SLR模型

•给定SLR模型，均方误差MSE可以写为

$R(a,b)=\frac{1}{n} ∑_{i=1}^n(y_i-(a+bx_i ))^2$ 

•优化任务：如何计算最优的参数组合

$R(a,b)={arg\ min}_{(a,b)}\ \frac{1}{n} ∑_{i=1}^n(y_i-(a+bx_i ))^2$

•数学工具：

–计算变量(a,b)的一阶偏导，令一阶偏导为0，从而求解(a ̂,b ̂ ):

$a ̂=y ̅-bx ̅，$其中y ̅和x ̅分别y和x的均值

⟹$b ̂=\frac{(∑_{i=1}^n(x_i-x ̅ )(y_i-y ̅ ))}{(∑_{i=1}^n(x_i-x ̅ )^2 )}$

令$σ_x^2=∑_{i=1}^n(x_i-x ̅ )^2 $

$r⋅σ_x σ_y=∑_{i=1}^n(x_i-x ̅ )(y_i-y ̅ )$

r为皮尔森相关系数

$b ̂=r σ_y/σ_x  ;  a ̂=y ̅-b ̂x ̅$

皮尔森相关系数：


![image-20231209193140015](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209193140015.png)

![image-20231209193537774](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209193537774.png)

•多元线性回归（Multiple Linear Regression, MLR）

–在简单（一元）线性回归SLR模型基础上添加更多的独立变量

•多元线性回归的一般形式

$y ̂=θ_0+θ_1 x_1+θ_2 x_2+…θ_d x_d=θ_0+∑_{j=1}^dθ_d x_d$

•针对每个数据点，添加一个常数特征$x_0=1$，得到

$y ̂=∑_{j=0}^dθ_d x_d $

•基本概念：

–输入变量$x_1,x_2,…,x_d$也称：特征（Feature）、协变量（Covariate)、解释变量（Explanatory Variable）、回归量（Regressor）

–参数$θ_1,θ_2,…,θ_d$度量了输入变量对预测值的权重

–参数$θ_0$为截距项

![image-20231209193835626](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209193835626.png)

![image-20231209194653304](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209194653304.png)

![image-20231209194711455](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209194711455.png)

–二维空间（记作$R^2$）中两个向量$v_1$和$v_2$的张成空间$span(v_1,v_2)$的直观几何含义取决于两个向量是否线性无关,若无关则是二维平面。

![image-20231209195001905](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195001905.png)

![image-20231209195043691](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195043691.png)

![image-20231209195244685](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195244685.png)

![image-20231209195324137](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195324137.png)

![image-20231209195333251](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195333251.png)





![image-20231209195357033](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195357033.png)

![image-20231209195429023](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195429023.png)

凸函数情况下，局部最优解就是全局最优解

•学习率的选择

–过大的学习率导致学习的不稳定，甚至不能收敛

•如之前的“螺旋上升”现象

–过小的学习率导致训练步数多读

•导致过长的训练时间

![image-20231209195802521](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195802521.png)

![image-20231209195817055](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231209195817055.png)

SGD不用载入所有数据点，可以将其视为梯度下降优化的随机逼近，因为它用其估计值代替实际梯度。

## 分类问题与决策树分类器

典型的机器学习问题：

分类、回归、聚类

### 分类与监督学习

监督学习步骤：

* 提出问题（Question）
* 准备数据（Input data）
* 选择特征（Features）
* 标注数据（Labels）
* 学习算法（Algorithm）
* 评价模型（Evaluation）

分类基本步骤：

**Question->Data->Features->Algorithm->Evaluation**

![image-20231213125325772](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231213125325772.png)

![image-20231213125352018](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231213125352018.png)

决策树训练算法：

![image-20231213130607127](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231213130607127.png)

度量混杂度：

将离散属性建模为随机变量

引入信息熵：
$$
h(x)=log_2(\frac{1}{p(x)})\\
对于给定随机变量X，X的熵：\\
H(X)=\sum^{|C|}_{c=1}p(x_c)h(x_c)=-\sum^{|C|}_{c=1}p(x_c)log_2(p(x_c))
$$
熵越高，越难预测。

只与随机变量的取值个数和概率有关。

熵可以用来度量平均的最短描述长度。

条件熵（conditional entropy）：
$$
定义符号：h(x|y)=log_2(\frac{1}{p(x|y)})\\
条件熵：\\
H(x|y)=E_{x,y}[h(x|y)]\\
\sum_x\sum_yp(x,y)log_2(\frac{1}{p(x|y)})
$$
**直观含义：**给定随机变量X和Y的联合概率分布，假设Y是已知的，我们能从X中获得多少信息量？

联合熵：
$$
H(X,A)=-\sum^{|c|}_{c=1}\sum^{|A|}_{a=1}P(c,a)logP(c,a)\\
若X与A独立，则:\\P(c,a)=P(c)P(a),H(X,A)=H(X)+H(A)\\
H(X|A)=\sum^{|A|}_{a=1}P(A=a)H(X|A=a)\\
H(A,X)=H(A)+H(X|A)\\
若X，a独立，则：\\
H(X|A)=H(X)\\
$$
信息增益：给定随机变量A后，X减少的不确定性：
$$
IG(X|A)=H(X)-H(X|A)\\
=H(X)-\sum_jP(A=a_j)H(X|A=a_j)
\\性质：
𝐼𝐺(𝑋|𝐴)=𝐼𝐺(𝐴|𝑋)\\

𝐼𝐺(𝑋|𝑋)=𝐻(𝑋)\\
𝐼𝐺(𝑋|𝐴)=𝐻(𝑋)+𝐻(𝐴)−𝐻(𝑋,𝐴)\\
当只有两种可能时：\\
𝐻(𝑋│𝐴)=𝐻(𝑋|𝐴=𝑎1)𝑃(𝐴=𝑎1)+𝐻(𝑋|𝐴=𝑎2)𝑃(𝐴=𝑎2)
$$
![image-20231214123420859](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231214123420859.png)

![image-20231214123444678](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231214123444678.png)

IG不是唯一选择，也可以使用GINI系数

![image-20231214123354785](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231214123354785.png)

## 分类问题与线性分类器

**逻辑回归**

非线性函数的性质：

* 输出在[0,1]
* 能定义损失函数

![image-20231214132757631](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231214132757631.png)

![image-20231214132804777](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231214132804777.png)

![image-20231214132850656](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231214132850656.png)

**寻找新的损失函数**

原因：

沿用MSE的话，对于非凸函数会陷入局部最优，不同初值导致不同解。

==交叉熵是ln 熵是log2==

![image-20231214133500434](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231214133500434.png)

![image-20231214133606516](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231214133606516.png)

==极大似然估计等价于最小化交叉熵==

### 感知机模型

仍然是用F1指标等进行评价，感知机针对于二分类。

![image-20231217143009725](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217143009725.png)

对于线性可分数据，可在有限步迭代后收敛。

目标是实现所有分类正确（线性可分数据）

分类错误可表示为：

$-y_i (⟨w,x_i ⟩+b)>0$

定义损失函数：


$L(w,b)=-∑_{x_i∈M}y_i (⟨w,x_i ⟩+b) $

(针对于整个训练集)

M为所有错误分类实例的集合。

> 感知机模型的基本形式可以表示为：
>
> 1. 输入：\( $\mathbf{x} = (x_1, x_2, \ldots, x_n)$ \)，是输入特征向量。
> 2. 权重：$ \mathbf{w} = (w_1, w_2, \ldots, w_n) $，是每个特征对应的权重。
> 3. 输出：\( y \)，是二元分类的输出。
>
> 感知机模型的输出 \( y \) 可以通过以下公式计算：
>
> $ y = \begin{cases} 1, & \text{if } \sum_{i=1}^{n} w_i x_i + b > 0 \\ -1, & \text{otherwise} \end{cases} $
>
> 其中，\( b \) 是阈值（偏置项）。
>
> $可以将阈值 b  合并到权重中，令  w_0 = b ，并在输入向量  \mathbf{x} 中引入一个额外的分量  x_0 = 1 。\\这样，感知机输出可以写成更紧凑的形式：$
>
> \[ $y = \begin{cases} 1, & \text{if } \sum_{i=0}^{n} w_i x_i > 0 \\ -1, & \text{otherwise} \end{cases} $\]
>
> 这使得感知机模型的输出变为：
>
> \[ $y = \text{sign}(\mathbf{w} \cdot \mathbf{x}) $\]
>
> 其中 \($ \cdot$ \) 表示向量的点积，\($\text{sign}$\) 是符号函数，如果输入大于零则输出1，否则输出-1。
>
> 感知机学习算法的关键是通过梯度下降法不断调整权重 \($ \mathbf{w}$ \) 以使得分类结果更接近实际标签。在实际应用中，为了处理非线性问题，通常会使用更复杂的神经网络结构，例如多层感知机（MLP）。

![image-20231217144636230](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217144636230.png)

![image-20231217144651032](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217144651032.png)

若给定损失函数：

$[ L(\mathbf{w}, b) = \frac{1}{2} \sum_{i} (y_i - (\langle \mathbf{w}, \mathbf{x}_i \rangle + b))^2 ]$

求梯度后更新参数：

$ \mathbf{w} \leftarrow \mathbf{w} - \eta \sum_i (y_i - (\langle \mathbf{w}, \mathbf{x}_i \rangle + b)) \cdot \mathbf{x}_i$ 

其中，$\eta$是学习率，影响参数更新的步长。这个更新规则使得模型朝着梯度的反方向更新，以减小损失函数值。



Hinge Loss:

\[ $L(y, f(\mathbf{x})) = \max(0, 1 - y \cdot f(\mathbf{x})) $\]

可以增强鲁棒性，用于带边距感知机。比如SVM（支持向量机）

目标是：最大化分类边距。

具有较好的泛化能力。

在高维空间，如何计算边距大小？

![image-20231217150044603](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217150044603.png)

![image-20231217150055202](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217150055202.png)

![image-20231217150125230](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217150125230.png)

软间隔：

允许存在分类错误。

![image-20231217151540247](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217151540247.png)

C为超参数，越大表示对错误分类容忍度越低。

$ξ_i$是用于记录发生错误分类的变量。

原问题等价于：


![image-20231217151638643](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217151638643.png)

![image-20231217151803900](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217151803900.png)

## 聚类与无监督学习

无监督学习：
只有输入特征，没有目标类别，目标是发现数据内在的规律和结构。

优点：

节省标注成本。适用于有些无法实现确定目标类别的情况。

聚类的评价

* 熵

  ![image-20231217201114402](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217201114402.png)

==注意：这里的log是指log2==

k-均值聚类

![image-20231217204029450](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204029450.png)

![image-20231217204036184](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204036184.png)

![image-20231217204140731](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204140731.png)

![image-20231217204146214](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204146214.png)

![image-20231217204152496](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204152496.png)

可能会陷入局部最优解。

![image-20231217204251426](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204251426.png)

![image-20231217204304170](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204304170.png)

![image-20231217204400912](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204400912.png)

软聚类算法。

![image-20231217204426344](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217204426344.png)

![image-20231217205012197](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217205012197.png)

![image-20231217205113379](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217205113379.png)

![image-20231217205224647](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217205224647.png)

![image-20231217205255868](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217205255868.png)

![image-20231217205234517](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217205234517.png)

•K-Means是EM的特殊情况

–只考虑类簇的均值，而不考虑类簇方差

–优化目标等价于极大似然估计

![image-20231217205415319](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217205415319.png)

![image-20231217205421342](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217205421342.png)

![image-20231217205434142](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231217205434142.png)

## 文本表达



### 独热表达（one hot）

词的独热表示是一种最简单最直接的词的[向量化](https://so.csdn.net/so/search?q=向量化&spm=1001.2101.3001.7020)表示方式。主要步骤包含两步：

- 对需要用到的文本中所有词进行编码（假设共用N个词），每个词有唯一的下标（0~N）。
- 根据词下标 i 生成一个长度为N的向量，除了第i位为1外，其他位都为0。

例如，假设有一种特征“颜色”，其取值为“红色”、“绿色”、“蓝色”。将该特征进行独热表达后，将得到三个向量：

```
红色：[1, 0, 0]
绿色：[0, 1, 0]
蓝色：[0, 0, 1]

```

相似度的一种计算方式：

![image-20231219125324003](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219125324003.png)



![image-20231219125546862](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219125546862.png)

![image-20231219125649207](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219125649207.png)

tf：单词出现次数除以总词数。

$tf-idf(t,d)=tf(t,d)∗IDF(t)$

如果词未出现，记为0.

![image-20231219130407864](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219130407864.png)

### 分布式表达

独热表达从语义表达角度看，高维，稀疏，进步空间巨大。

任意不同单词的语义无关。但与自然语言不符合。

泛化性差。

![image-20231219130615982](C:\Users\Baijy\Desktop\image-20231219130615982.png)

![image-20231219130709168](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219130709168.png)

优势：

•降低表达维度，更少的参数和存储空间

•能够承载语义信息和运算

![image-20231219130802965](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219130802965.png)

如何学习到分布式表达？

**文档内共现/上下文共现（话题模型/词嵌入模型）**

#### 话题模型

LSI浅语义索引（LSA）

基于矩阵分解的话题模型

通过求解单词-文档共现矩阵的低秩近似4来得到话题。

![image-20231219132302599](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219132302599.png)

第一步：对单词-文档共现矩阵进行分解

SVD $D=U\sum V^T$

![image-20231219132510790](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219132510790.png)

![image-20231219132534785](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219132534785.png)

![image-20231219133116723](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219133116723.png)

![image-20231219133425035](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219133425035.png)

![image-20231219133434704](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219133434704.png)

![image-20231219133520782](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219133520782.png)

![image-20231219133528826](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219133528826.png)

![image-20231219133805918](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219133805918.png)

![image-20231219134053152](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219134053152.png)

#### 词嵌入

word2vec

![image-20231219134145026](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219134145026.png)

##### 工作过程：

###### 1.1 构建词汇表：
首先，构建一个包含文本数据中所有唯一词汇的词汇表。每个词汇都会被分配一个唯一的索引。

###### 1.2 上下文窗口：
对于每个训练样本，选择一个目标词，然后确定一个上下文窗口。上下文窗口定义了在预测目标词时要考虑的周围词的范围。

###### 1.3 数据编码：
将文本数据转换为模型可用的输入输出形式。每个训练样本由上下文中的词汇的词向量表示，并且目标词汇被编码为独热编码或其他适当的形式。

##### 2. 模型构建：

###### 2.1 输入层：
对于CBOW，输入层的节点数等于上下文窗口中的词汇数目乘以每个词汇的词向量维度。每个输入节点对应一个上下文词的词向量。

###### 2.2 隐藏层：
隐藏层的节点数是模型设计中的一个超参数。这一层的目标是学习将输入词汇的词向量组合成表示整个上下文的信息。

###### 2.3 输出层：
输出层的节点数等于词汇表的词汇数目。输出层的目标是预测目标词汇。通常使用softmax激活函数将输出转换为概率分布。

##### 3. 训练模型：

###### 3.1 损失函数：
定义一个损失函数，通常使用交叉熵损失函数，用于度量模型预测与实际目标的差异。

###### 3.2 反向传播：
使用反向传播算法和梯度下降优化算法，通过最小化损失函数来调整模型的权重。这将使模型能够更准确地预测目标词。

###### 3.3 迭代训练：
迭代训练过程中，模型将多次通过整个训练数据集，逐渐提升对目标词的预测性能。

##### 4. 获取词向量：

一旦模型训练完成，可以从隐藏层提取学习到的词向量。这些词向量可以用于表示每个词汇在语义空间中的位置，从而能够捕捉词汇之间的语义关系。

![image-20231219142225336](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142225336.png)

![image-20231219142239083](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142239083.png)

![image-20231219142252083](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142252083.png)

![image-20231219142320344](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142320344.png)

![image-20231219142339755](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142339755.png)

**主要区别：**

- **CBOW：**
  - 预测目标词，给定上下文。
  - 适用于小型数据集，语境相对一致的情况。
- **Skip-gram：**
  - 预测上下文，给定目标词。
  - 适用于大型数据集，语境变化较大的情况。

### 文本数据分类

举例：

* 话题分类
* 情感分析（识别人类感情）
* ![image-20231219142620695](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142620695.png)

![image-20231219142715066](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142715066.png)

方法：

* 人工分类![image-20231219142748259](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142748259.png)
* 基于规则![image-20231219142804744](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142804744.png)
* 基于统计学习![image-20231219142824313](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219142824313.png)
* ![image-20231219143156136](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143156136.png)
* ![image-20231219143356397](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143356397.png)
* ![image-20231219143414533](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143414533.png)
* ![image-20231219143427369](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143427369.png)
* ![image-20231219143436468](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143436468.png)
* ![image-20231219143443963](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143443963.png)
* ![image-20231219143454085](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143454085.png)
* ![image-20231219143503848](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143503848.png)
* ![image-20231219143513209](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143513209.png)
* ![image-20231219143847797](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143847797.png)

朴素贝叶斯的问题：

* ![image-20231219143939443](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143939443.png)
* ![image-20231219143946583](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143946583.png)
* ![image-20231219143955632](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219143955632.png)
* 假设二：与位置无关。
* ![image-20231219144057577](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219144057577.png)

## 网络数据分析

衡量节点中心性：

![image-20231219155050840](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219155050840.png)

度/（节点数-1）

`-1`是为了标准化到01之间（最大取1）。

==记得减1==

![image-20231219155206634](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219155206634.png)

### 结点中心度分析

不同节点的“地位”可能是不平等的。

哪些结点更重要？

**基于几何图形的度量方法closeness centrality**

![image-20231219160817504](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219160817504.png)

![image-20231219160900179](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219160900179.png)
$$
BC(v) = \sum_{s \neq v \neq t} \frac{\sigma_{st}(v)}{\sigma_{st}}
$$

- BC(v) 表示节点 v 的中介中心性
- *σ**s**t* 表示任意两个节点 s 和 t 的最短路径的总数
- *σ**s**t*(*v*) 表示任意两个节点 s 和 t 的最短路径中经过节点 v 的次数
- 在无权重网络中，*σ**s**t* 是路径包含边的数量求和；在加权网络中，*σ**s**t* 是路径包含边的权重求和。

图中给出的是标准化后的结果，对有向图应该去掉2.

### 社区

![image-20231219162136734](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219162136734.png)



优化目标：度量划分的紧凑型

![image-20231219162204204](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219162204204.png)

![image-20231219162221319](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219162221319.png)

![image-20231219162231243](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219162231243.png)

![image-20231219162259747](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219162259747.png)

![image-20231219162305621](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219162305621.png)

•Phase 1：以局部方式，优化模块度函数，将每个顶点归到“最好”的类簇中，直到所有的顶点所属的类簇不再变化为止 – **one_level**

–计算将节点i合并到邻居j所在社区的modularity增益ΔQ

–将节点i合并到能够产生最大增益ΔQ的节点j的社区中

–循环执行上述步骤，直到合并操作不再产生modularity的增益

==如何计算将i合并到社区C中的modularity增益ΔQ？==

–计算ΔQ(i→C)

–计算ΔQ(D→i)，即将节点 i移除原本的社区D

ΔQ=ΔQ(i→C)+ΔQ(D→i)

•Phase 2：把一个类簇中的所有顶点聚集抽象为一个超级顶点，重建一个网络，其中的每个顶点对应一个社区 – **induced_graph**

![image-20231219162714178](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231219162714178.png)

算法运行示例：

* 随机选择顺序遍历结点
* 按顺序访问邻居，计算分值，把点并入分值最大的社区。
* 多次遍历
* 最后，检查new_mod – old_mod是否足够小

## pagerank与影响力分析

基本思想：为不同的入边赋予不同的权值。

指向v的结点的pagerank值越高，则入边权重越高。

比指向v的结点指向其他结点的数目越多，对v相应入边的权重降低。

数学表示

![image-20231221130759865](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221130759865.png)

![image-20231221130810867](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221130810867.png)

![image-20231221130818326](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221130818326.png)

![image-20231221130828919](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221130828919.png)

![image-20231221130930282](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221130930282.png)

![image-20231221131704640](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221131704640.png)

==一个马尔科夫链存在唯一的稳态分布，当且仅当它是不可约的遍历链==

直观解释：强连通有向图.

![image-20231221201615002](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221201615002.png)

![image-20231221201657971](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221201657971.png)

![image-20231221201755565](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221201755565.png)

![image-20231221201811983](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221201811983.png)

dangling节点（悬空节点，有向图中出度为0）可能导致不收敛。（如果是传统pagerank，出度为0会导致pagerank值一直为0.

解决办法是，让该节点与所有结点都建立一条邻边，修改邻接矩阵。

比如：
![image-20231221203152296](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221203152296.png)

（这会带来一定的偏差）

### 社交影响力（social influence）

应用：病毒营销

建立有向图模型

![image-20231221204202514](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221204202514.png)

![image-20231221204245703](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221204245703.png)

![image-20231221204253806](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221204253806.png)

![image-20231221204303953](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221204303953.png)

NP-Hard问题.

解决思路：

![image-20231221204407821](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221204407821.png)

![image-20231221204455731](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221204455731.png)

•基本想法

–出度越高的点，影响力越大

–选择的种子节点的影响范围避免重叠

![image-20231221205207391](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205207391.png)

![image-20231221205214635](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205214635.png)

![image-20231221205221732](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205221732.png)

![image-20231221205233522](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205233522.png)

局限性：

只考虑了直接邻居的影响。

间接影响力：考虑两点路径。

![image-20231221205311140](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205311140.png)

![image-20231221205353533](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205353533.png)

设定一个阈值Threshold，如果路径的激活概率小于阈值，则忽略

![image-20231221205421707](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205421707.png)

![image-20231221205432159](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205432159.png)



具体来说，设$ \(f: 2^V \rightarrow \mathbb{R}\)$ 是定义在集合 \(V\) 上的函数，其中 $\(2^V\) $表示 \(V\) 的所有子集的集合。函数 \(f\) 被称为次模的，如果对于任意两个集合 \($A \subseteq B \subseteq V$\) 和任意的元素 \($v \in V \setminus B$\)，都有以下不等式成立：

\[ $f(A \cup \{v\}) - f(A) \geq f(B \cup \{v\}) - f(B) $\]

这个不等式表示，往一个较小的集合中添加元素的边际效应大于或等于往一个较大的集合中添加同一个元素的边际效应。直观上来说，次模性可以理解为新添加的元素对于较小集合的影响较大，但对于较大集合的影响逐渐减小。

![image-20231221205711080](C:\Users\Baijy\AppData\Roaming\Typora\typora-user-images\image-20231221205711080.png)

`2023.12.21 21:07`



## 复习课
