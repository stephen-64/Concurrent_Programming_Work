package main

import java.util.concurrent.locks.ReentrantLock
import java.util.Random
import java.util.concurrent.atomic.AtomicBoolean

/**
 * A extension of LimitedQueue that manages customers in the line-ups checking
 * if they have been served and serving them if they have not
 * and then removing them for the line-up
 * and setting the time theu spent waiting
*/
class line_ups(length:Int,clock:SpeedyClock): LimitedQueue<Customer>(length),Runnable {
	
	var local_clock = clock
	var rand = Random()
	// A locking variable used to prevent additions in critical queue work
	var hold = AtomicBoolean(false)
	
	override fun run(){
		while(true){
			if(super.peek()!=null){
				var start_wait_time:Int = local_clock.get_time().to_sec();
				var wait_time:Int = 300+rand.nextInt(301)
				var clock_tracker:Int = start_wait_time
				var loop = clock_tracker - start_wait_time
				while(loop <= wait_time){
					hold.set(true)
					clock_tracker = local_clock.get_time().to_sec()
					loop = (clock_tracker - start_wait_time)
				}
				hold.set(false)
				super.peek().set_end_time(local_clock.get_time())
				super.peek().set_served(true)
				super.poll()
			}
		}
	}
	
	override fun add(element:Customer):Boolean{
		if(hold.get()){
			return false
		}
		if(super.add(element)){
			//lock2.unlock()
			return true
		}else{
			//lock2.unlock()
			return false
		}
		
	}
	
}