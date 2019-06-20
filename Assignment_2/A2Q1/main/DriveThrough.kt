package main

import java.util.concurrent.locks.ReentrantLock

/**
 * The representation of the DriveThrough contains 2 Queues that merge into 1
 * at a "Window" which distributes the
 * the customers to the workers for processing purposes   
*/
class DriveThrough(clock:SpeedyClock) : Thread(){
	
	init{
		super.setDaemon(true)
	}
	
	var q1 = line_ups(3,clock)
	var q2 = line_ups(3,clock)
	var current_cust:Customer? = null
	var win:Window=Window()
	var last_q1:Boolean = false
	var last_q1_proc = false
	var lock = ReentrantLock()
	
	/**
	 * Ran concurrently to 
	 * fairly distribute the customers waiting in the
	 * respective queues to the window to fill their order
	*/
	override fun run(){
		var t1 = Thread(q1)
		var t2 = Thread(q2)
		t1.setDaemon(true)
		t2.setDaemon(true)
		t1.start()
		t2.start()
		win.start()
		while(true){
			//lock.lock()
			if(last_q1_proc){
				var wc = q2.peek()
				if(wc!=null){
				if(!win.add_cust(wc)){
					
				}
			}
				last_q1_proc=false
			}else{
				var wc = q1.peek()
				if(wc!=null){
				if(!win.add_cust(wc)){
								
				}
				last_q1_proc=true
			}
		}
		}
	}
	
	/**
	 * Adds a customer to the queues insuring fiar division across both queues
	*/
	fun add_cust(c:Customer):Boolean{
		if(last_q1){
			if(q2.add(c)){
				last_q1=false
				return true
			}else if(q1.add(c)){
				last_q1=true
				return true
			}else{
				return false
			}
		}else{
			if(q1.add(c)){
				last_q1=true
				return true
			}else if(q2.add(c)){
				last_q1=false
				return true
			}else{
				return false
			}
		}
	}
	
}