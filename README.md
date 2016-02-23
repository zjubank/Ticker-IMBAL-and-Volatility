# Ticker-IMBAL-and-Volatility
计算一些奇奇怪怪的股票数据。

## 第一，每日每股的订单不平衡指标
Order imbalance（IMBAL）:用所有买单的数量除以买单和卖单数量之和 （都是五档的报价）
统计频率：
1. 每日IMBAL
2. 以沪深300指数下跌到5%那一时刻为节点，统计开盘到下跌5%之间的IMBAL，标记为pre5-IMBAL
3. 以沪深300指数下跌到7%那一时刻为节点，统计5%-7%之间的IMBAL，标记为57-IMBAL;7%之后的，记为post7-IMBAL。
下跌到5%指第一次到5%

## 第二，每日每股的波动率指标
Volatility：用所有成交价格，计算标准差
统计频率：
1. 每日Volatility
2. 以沪深300指数下跌到5%那一时刻为节点，统计开盘到下跌5%之间的Volatility，标记为pre5- Volatility
3. 以沪深300指数下跌到7%那一时刻为节点，统计5%-7%之间的Volatility，标记为57- Volatility ;之后的，记为post7- Volatility
