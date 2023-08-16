[TOC]

## PisCo 线程池
- Linux下基于std::thread的c++高效率线程池
- 基于std::thread、 std::atomic 以及std::feature等现代 C++11 标准库的特性来实现线程池
- 总的来说，这个线程池的实现比较简单、易于理解，同时也具有良好的性能和可扩展性，可以满足大多数多线程编程需求。当然，如果你需要更加复杂的线程池实现，可以参考一些成熟的线程池库，如 Boost.Thread、Poco::ThreadPool 等。

## 核心逻辑
- core thread：通过配置文件获取，默认3
- max  thread：通过配置文件获取，默认是系统支持的最大线程数
- task  queue：通过配置文件获取，默认10000，需要控制任务的最大数量，防止数量持续增大，导致资源耗尽。
策略：
<table>
	<tr><th>AbortPolicy</th><th>拒绝并抛出异常</th></tr>
    <tr><th>CallerRunsPolicy</th><th>使用当前调用的线程来执行此任务</th></tr>
    <tr><th>DiscardOldestPolicy</th><th>抛弃队列头部（最旧）的一个任务，并执行当前任务</th></tr>
    <tr><th>DiscardPolicy</th><th>忽略并抛弃当前任务</th></tr>
<table>

- keepAliveTime: 通过配置文件获取，默认5分钟，空闲线程的存活时间


