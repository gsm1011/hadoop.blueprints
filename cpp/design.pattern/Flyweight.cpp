// This pattern is an object that minimizes memory usage by sharing as
// much data as possible with other similiar objects. It is a way to
// use objects in large numbers when a simple repeated representation
// would use an unacceptable amount of memory. Often, some parts of
// the object states can be shared. We can hold them in external data
// structures and pass them to the flyweight objects temporarily when
// they are used.


