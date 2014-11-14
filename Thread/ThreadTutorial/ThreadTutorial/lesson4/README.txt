lesson4

Future
Header with facilities that allow asynchronous access to values set by specific providers, possibly in a different thread.
Future头文件中包含了允许通过提供者异步访问数据集合的工具类。这些数据集合可能在不同的线程中。

Each of these providers (which are either promise or packaged_task objects, or calls to async) share access to a shared state with a future object: the point where the provider makes the shared state ready is synchronized with the point the future object accesses the shared state.
每一个提供者（可能是promise或者packaged_task或者是对async的调用）通过一个future对象共享对共享状态的访问。提供者使得共享状态为Ready的操作和future对象访问共享状态的操作是同步的。

Promise
A promise is an object that can store a value of type T to be retrieved by a future object (possibly in another thread), offering a synchronization point.
promise是一个提供了同步点的对象，它可以存储类型为T的值，这个值可以被一个future对象（可能是在另一个线程中）接收到。

On construction, promise objects are associated to a new shared state on which they can store either a value of type T or an exception derived from std::exception.
在构造的时候，promise对象和一个新的共享状态关联，在这个共享状态上，它可以存储一个类型为T的值或者是一个从std::exception派生而来的异常。

This shared state can be associated to a future object by calling member get_future. After the call, both objects share the same shared state:
- The promise object is the asynchronous provider and is expected to set a value for the shared state at some point.
- The future object is an asynchronous return object that can retrieve the value of the shared state, waiting for it to be ready, if necessary.
这个共享状态可以通过调用get_future来和一个future对象关联。调用get_future以后，promise和future就共享同一个共享状态。
- promise对象是同步的提供者，在某个时间点它将为共享状态设置一个值。
- future对象是同步返回的对象，它可以获得共享状态的值，如果需要的话，它会等待共享状态变为ready。

The lifetime of the shared state lasts at least until the last object with which it is associated releases it or is destroyed. Therefore it can survive the promise object that obtained it in the first place if associated also to a future.
共享状态的生命周期一直持续到和他关联的最后一个对象释放它或者被销毁。所以当天它依然和一个future关联的时候，它不会随持有它的promise对象的销毁而销毁。





