fn main() {

    let array = [12,7,8,4,2,9,1];
    let mut rez = array[0];
    for index in 1..7 
    {
       if array[index] < rez
       {
           rez = array[index];
       }
    }
    println!("{}", rez);
}