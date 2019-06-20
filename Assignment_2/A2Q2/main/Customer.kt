package main

import java.util.concurrent.atomic.AtomicBoolean

/**
 * The internal representation of a customer holds data such as who served them
 * wether they have been served and how long they had to wait before being served
 * by someone 
*/
class Customer(t:Time) {
	var start_time:Time = t
	var end_time:Time = Time()
	var has_been_served:AtomicBoolean = AtomicBoolean(false)
	var server:Int =0
	var wait_time:Int = 0
	
	fun get_start_time():Time{
		return start_time
	}
	
	fun get_end_time():Time{
		return end_time
	}
	
	fun set_end_time(t:Time){
		end_time = t
		wait_time = end_time.to_sec() - start_time.to_sec()
	}
	
	fun get_wait_time():Int{
		return wait_time
	}
	
	fun served():Boolean{
		return has_been_served.get()
	}
	
	fun set_served(state:Boolean){
		has_been_served.set(state)
	}
	
	fun set_server(server:Int){
		this.server = server
	}
	
}