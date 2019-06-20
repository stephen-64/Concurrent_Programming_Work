package main

import java.util.concurrent.ConcurrentLinkedQueue
import java.util.concurrent.locks.ReentrantLock
import java.util.concurrent.atomic.AtomicInteger

/**
 * A thread safe size restricted queue for use as customer
 * waiting points in this program
*/
open class LimitedQueue<e> (size:Int) : ConcurrentLinkedQueue<e>() {

	val max_size:Int=size
	var num_items = AtomicInteger(0)
	var lock = ReentrantLock()
	
	override fun add(element:e):Boolean{
		lock.lock()
		if(num_items.get() < max_size){
			num_items.getAndIncrement()
			lock.unlock()
			return super.add(element)
		}else{
			lock.unlock()
			return false
		}
		
	}
	
	override fun poll():e{
		lock.lock()
		num_items.getAndDecrement()
		lock.unlock()
		return super.poll()
	}
	
}