pub fn has_substring(search: &str, find: &str) -> bool {
    // Any non-brute-force algorithm would be too difficult to implement in an
    // interview without reference so implement the naive O(nm) solution.
    if search.is_empty() {
        return find.is_empty();
    }

    let search_bytes = search.as_bytes();
    let find_bytes = find.as_bytes();
    let max_search_index = search_bytes.len() - find_bytes.len();

    for i in 0..(max_search_index + 1) {
        let mut found = true;
        for j in 0..find_bytes.len() {
            if search_bytes[i + j] != find_bytes[j] {
                found = false;
                break;
            }
        }
        if found {
            println!("Sub string found {}", i+1);
            return true;
        }
    }
    println!("not found");
    return false
}

fn main() {
    assert!(has_substring("abcdef", "yty"));
}