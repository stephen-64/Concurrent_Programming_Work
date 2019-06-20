package main

import java.util.concurrent.atomic.AtomicBoolean
import java.util.concurrent.locks.ReentrantLock

/**
 * The drivethrough window tracks which crew member
 * is to handle which customer distrbuting the work
 * fairly between the workers(Crew)
*/
class Window:Thread(){
	
	init{
		super.setDaemon(true)
	}
	
	
	var next_cust:Customer? = null
	var has_cust:AtomicBoolean = AtomicBoolean(false)
	
	var crew1 = Crew(1)
	var crew2 = Crew(2)
	
	var last_crew1 = false
	
	var lock = ReentrantLock()
	
	
	override fun run(){
		crew1.start()
		crew2.start()
		while(true){
			lock.lock()
			while(has_cust.get()){
				if(last_crew1){
					crew2.set_cust(next_cust)
					last_crew1=false
//					while(crew2.is_busy.get()){
//						//Thread.sleep(1)
//					}
					has_cust.set(false)
				}else{
					crew1.set_cust(next_cust)
					last_crew1=true
//					while(crew1.is_busy.get()){
//						//Thread.sleep(1)
//					}
					has_cust.set(false)
				}
			}
			next_cust=null
			has_cust.set(false)
			lock.unlock()
		}
	}
	
	fun add_cust(c:Customer):Boolean{
		lock.lock()
		if(next_cust==null && !has_cust.get()){
			next_cust=c
			has_cust.set(true)
			lock.unlock()
			return true
		}else{
			lock.unlock()
			return false
		}
				
	}
	
}