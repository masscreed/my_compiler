fn main() {
 
    let mut a = 8;
    let mut b = 20;
    let c;
    while a > 0 && b > 0
    {
        if a > b
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }        
    }
    c = a + b;
   
   println!("{}", c);
}