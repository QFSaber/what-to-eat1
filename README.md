# APP_Gandalf —— 选择困难者的福音

一个基于 **Qt (C++)** 开发的桌面小工具，用来帮「选择困难症」用户随机决定：

- 今天吃啥（分为 **南区菜** 和 **北区菜** 两类）
- 今天喝啥（**饮料** 类）

数据保存在本地 **MySQL** 数据库中，支持添加菜品/饮料、随机抽选。

---

## 功能特性

| 功能 | 说明 |
| --- | --- |
| 启动页 | 显示欢迎背景图与「开始使用」按钮 |
| 随机选菜 | 分「南区随机」「北区随机」两个按钮，点击后从数据库随机抽取一个菜名展示 |
| 随机选饮料 | 点击「随机饮料」从饮料表随机抽取 |
| 添加菜品 | 选择「南区 / 北区」后输入菜名，写入对应数据表 |
| 添加饮料 | 输入饮料名写入饮料表 |
| 返回 | 返回上一级菜单 |

窗口固定大小 **600 × 300**，标题为「选择困难者的福音」。

---

## 项目结构

```
APP_Gandalf/
├── APP_Gandalf.pro          # Qt 工程文件（core/gui/widgets/sql，C++17）
├── main.cpp                 # 程序入口，创建并显示启动页 MainWindow1
├── mainwindow1.h/.cpp/.ui   # 启动页（欢迎界面 + 开始按钮）
├── widget.h/.cpp/.ui        # 主窗口（QStackedWidget 多页面：选菜/选饮料/添加）
├── mysql.h/.cpp             # 数据库封装类 MySql（QODBC 连接 MySQL）
├── globals.h/.cpp           # 全局单例 Global::MS（MySql 实例）
├── res.qrc                  # Qt 资源文件（图片资源）
└── imge/                    # 图片资源目录（背景、图标、food/drink 图片）
```

### 类与模块说明

- **MainWindow1**：启动界面，通过 `paintEvent` 绘制背景图 `beijin.png` 与用户图标 `user.png`；点击「开始使用」关闭自身并打开 `Widget`。
- **Widget**：主界面，左侧为功能导航按钮（选菜 / 选饮料 / 添加菜品 / 添加饮料 / 返回），右侧 `QStackedWidget` 承载各页面；`paintEvent` 根据当前页面 `ui_index` 切换背景图。
- **MySql**：对 `QSqlDatabase` 的封装，提供：
  - `getNumber(South,North,Drink)` —— 统计某张表的记录数
  - `ShowData(INDEX,South,North,Drink)` —— 按序号取出某条记录的名称
  - `InsertData(name,South,North,Drink)` —— 向对应表插入一条记录
  - `DeleteData(name)` / `UpData()` —— 删除 / 更新（见下方「已知问题」）
- **Global**：在 `globals.cpp` 中定义全局 `MySql MS;` 实例，供各模块共享同一连接。

---

## 构建与运行

### 环境要求

- **Qt 5 / Qt 6**（开发记录使用 Qt 6.2.4 + MinGW 64-bit）
- C++17
- 本地 **MySQL** 服务，并安装 **MySQL ODBC 驱动**（程序使用 `QODBC` 驱动连接）
- `windeployqt`（用于发布时拷贝依赖）

### 编译步骤

使用 Qt Creator 打开 `APP_Gandalf.pro` 直接构建即可；或在 MinGW 终端中：

```bash
# 生成 Makefile
qmake APP_Gandalf.pro
# 编译
mingw32-make
```

### 打包发布（Windows）

参考源码注释中的流程，使用 `windeployqt` 拷贝运行依赖：

```bash
# 进入构建产物目录
cd /d <你的构建目录>/release
windeployqt APP_Gandalf.exe
```

---

## 数据库配置

程序在 `mysql.cpp` 中以如下参数连接本地 MySQL（通过 **QODBC**）：

| 配置项 | 值 |
| --- | --- |
| 驱动 | `QODBC` |
| 主机 | `127.0.0.1` |
| 端口 | `3306` |
| 数据库名 | `2` |
| 用户名 | `root` |
| 密码 | `123456789` |

### 所需数据表（依据代码推断）

程序访问以下数据表，需自行在 MySQL 中创建（数据库名为代码中的 `2`）：

```sql
-- 南区菜
CREATE TABLE south (
    id   INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

-- 北区菜
CREATE TABLE north (
    id   INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

-- 饮料
CREATE TABLE drink (
    id   INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

-- 以下两张表在代码中有所引用（插入/删除/更新逻辑），建议也预留
CREATE TABLE caidan (
    id   INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE users (
    user_id INT PRIMARY KEY,
    score   INT
);
```

> 实际表结构以你本机数据库为准；代码中对 `caidan`、`users` 的引用与 `south/north/drink` 的增删并不完全对应，详见下方「已知问题」。

---

## 已知问题 / 待改进点

> 该项目为学习/练手作品，部分实现可以继续完善：

1. **数据库连接被重复 `open()`**：`MySql` 构造函数中在设置主机、端口、账号之前就调用了一次 `db.open()`，属于冗余调用。
2. **增删表不一致**：`InsertData` 写入 `south/north/drink`，但 `DeleteData` 删除的是 `caidan` 表；`UpData()` 更新的是 `users` 表且为写死语句，且仅在 `caidan` 上做了一次无意义的 `SELECT`。删除/更新逻辑目前基本未与界面联动。
3. **全局实例未被使用**：`Global::MS` 已定义，但各按钮槽函数里几乎都新建了局部 `MySql MS;`，会反复建立连接。可统一改用全局单例。
4. **随机种子未设置**：使用 `rand()` 但未调用 `srand(time(nullptr))`，每次程序启动的随机序列相同。
5. **凭据硬编码**：数据库用户名/密码直接写在源码中，建议改为配置文件或环境变量。
6. **空页面**：`QStackedWidget` 的 index 4 对应一个空白 `page_6`，启动时 `setCurrentIndex(4)` 会显示空白页，需确认是否预期。

---

## 许可证

本项目为个人学习用途，暂无明确开源许可证。
