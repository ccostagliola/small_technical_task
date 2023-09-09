/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
class SingletonUniqueIdGenerator {
private:
    SingletonUniqueIdGenerator() :
        n(0)
    {}

public:
    SingletonUniqueIdGenerator(const SingletonUniqueIdGenerator&) = delete;
    SingletonUniqueIdGenerator& operator=(const SingletonUniqueIdGenerator &) = delete;
    SingletonUniqueIdGenerator(SingletonUniqueIdGenerator &&) = delete;
    SingletonUniqueIdGenerator& operator=(SingletonUniqueIdGenerator &&) = delete;

    /**
     * @brief Increments and returns the counter of his object,
     * 
     * @return int The value of the counter. It's always different.
     */
    int incrementAndReturn() {

        return ++n;
    }

    /**
     * @brief Returns the unique instance of this object. Note this is a static method.
     * 
     * @return SingletonUniqueIdGenerator& A reference to the unique instance of the object.
     */
    static SingletonUniqueIdGenerator& instance() {
        static SingletonUniqueIdGenerator singleton;

        return singleton;
    }

private:
    int n;
};