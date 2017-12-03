package org.dan.ubs.problem3;

import java.util.LinkedList;
import java.util.List;

public class BlockingQueueImpl {
    private final List queue;
    private final int limit;

    public BlockingQueueImpl() {
        this(new LinkedList(), 10);
    }

    public BlockingQueueImpl(List queue, int limit) {
        this.queue = queue;
        this.limit = limit;
    }

    public synchronized void enqueue(Object item) throws InterruptedException {
        while (limit <= queue.size()) {
            wait();
        }
        queue.add(item);
        notify();
    }

    public synchronized Object dequeue() throws InterruptedException {
        while (queue.isEmpty()) {
            wait();
        }
        notify();
        return queue.remove(0);
    }
}
