package main

import java.util.concurrent.atomic.AtomicBoolean
import java.util.concurrent.locks.ReentrantLock

/**
 * This class represents a crew member who is working
 * the drivethrough Window. They take a customer and
 * set if they have been served or not
 *
 */
class Crew(num:Int):Thread(){
	
	//A unique user set identifier for the Crew memeber 
	var mynum = num
	
	init{
		super.setDaemon(true)
	}
	
	
	var is_busy:AtomicBoolean = AtomicBoolean(false)
	var cust:Customer? = null
	var lock = ReentrantLock()
	
	
	/**
	 * This analysis if there is a customer
	 * delegated to this crew memeber and if so
	 * serves them
	*/
	override fun run(){
		while(true){
			lock.lock()
			var cc = cust
			if(is_busy.get() && cc!=null){
				cc.set_served(true)
				cc.set_server(mynum)
				cust=null
				is_busy.set(false)
			}
			lock.unlock()
		}
	}
	
	/**
	 * Set's the customer to be handeled by this worker
	 * each worker can only handle 1 customer at a time
	*/
	fun set_cust(c:Customer?):Boolean{
		lock.lock()
		if(cust==null && !is_busy.get()){
			cust = c
			is_busy.set(true)
			lock.unlock()
			return true
		}else{
			lock.unlock()
			return false
		}
	}
	
}