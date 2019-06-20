package main
import java.util.Random;
import java.util.Vector
import java.util.concurrent.ConcurrentLinkedQueue

/**
 * The main running function prepares the drivethrough and tracks statistics on the customers
*/
fun main(args:Array<String>){
	var clk = SpeedyClock((args[0]).toInt())
	var dt = DriveThrough(clk)
	var rand = Random()
	var cust_q = ConcurrentLinkedQueue<Customer>()
	var cust_holder = Vector<Customer>()
	var lined_cust = Vector<Customer>()
	var waiting_cust = ConcurrentLinkedQueue<Customer>()
	var waiting2_cust = ConcurrentLinkedQueue<Customer>()
	var stalled_cust = ConcurrentLinkedQueue<Customer>()
	var left_cust = ConcurrentLinkedQueue<Customer>()
	var last_cust_time:Time = Time()
	var current_time:Time
	clk.start()
	dt.start()
	while(clk.isAlive()){
		current_time=clk.get_time()
		if((current_time.to_sec() - last_cust_time.to_sec()) >= (50+rand.nextInt(51))){
			var c = Customer(current_time)
			cust_q.add(c)
			cust_holder.add(c)
			last_cust_time=current_time
		}
		
		for(cust in waiting_cust){
			if(dt.add_cust(cust)){
				waiting_cust.remove(cust)
			}
		}
		
		for(cust in waiting2_cust){
			if(dt.add_cust(cust)){
				waiting2_cust.remove(cust)
			}
		}
		
		
		if(!cust_q.isEmpty()){
			if(dt.add_cust(cust_q.peek())){
				lined_cust.add(cust_q.poll())
			}else{
				//println('f')
				waiting_cust.add(cust_q.poll())
			}
		}
		
		for(cust in waiting_cust){
			if((current_time.to_sec() - cust.start_time.to_sec()) <=20 ){
				stalled_cust.add(cust)
				waiting_cust.remove(cust)
			}
		}
		
		for(cust in stalled_cust){
			if((current_time.to_sec() - cust.start_time.to_sec()) <=600 ){
				waiting2_cust.add(cust)
				stalled_cust.remove(cust)
			}
		}
		
		for(cust in waiting2_cust){
			if((current_time.to_sec() - cust.start_time.to_sec()) <=600 ){
				left_cust.add(cust)
				waiting2_cust.remove(cust)
			}
		}
		
	}
	
	var customers_served = ConcurrentLinkedQueue<Customer>()
	
	var time_to_serve = 0
	
	for(cust in cust_holder){
		if(cust.served()){
			if(cust.end_time.to_sec()>0){
				customers_served.add(cust)
				time_to_serve += cust.wait_time
			}
		}
	}
	
	var avg_serve = time_to_serve/customers_served.size
	
	println("The simulation ran for " + args[0].toInt() +" mins and produced the following results:")
	println("" + cust_holder.size+" Customers arrived")
	println("" + (cust_holder.size-customers_served.size) + " Customers left without service")
	println("" + customers_served.size + " Customers were served")
	println("The average time taken to serve each customer was " + avg_serve + " seconds")
	
}