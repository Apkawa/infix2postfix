extern crate rand;
extern crate num;


use rand::Rng;

const OPEN_BRACKET_STATE: u8 =  1;
const CLOSE_BRACKET_STATE: u8 = 2;
const NUMBER_STATE: u8 = 3;
const OPERATOR_STATE: u8 = 4;

const OPERATORS: [char; 4] = ['/', '*', '-', '+'];
const OPEN_BRACKET: char = '(';
const CLOSE_BRACKET: char = ')';

static OPEN_BRACKET_STATE_ARRAY: [u8;2] = [OPEN_BRACKET_STATE, NUMBER_STATE];

fn randint(from:u32, to:u32) -> u32 {
    let mut rnd = rand::thread_rng();
    return rnd.gen_range(from, to);
}

fn get_number() -> u32 {
    return randint(1, 1024);
}
fn get_operator() -> char {
    let mut rnd = rand::thread_rng();
    return *rnd.choose(&OPERATORS).unwrap();
}


fn generate_infix(max_symbol_count: u64) {
    let mut rnd = rand::thread_rng();
    let mut state = *rnd.choose(&OPEN_BRACKET_STATE_ARRAY).unwrap();
    let mut bracket_num: i64 = 0;
    for i in 0 .. max_symbol_count {
        match  state {
            OPEN_BRACKET_STATE => {
                    state = NUMBER_STATE;
                    bracket_num += 1;
                    print!("{}", OPEN_BRACKET);
            },
            CLOSE_BRACKET_STATE => {
                    bracket_num -= 1;
                    state = OPERATOR_STATE;
                    print!("{}", CLOSE_BRACKET);
                },

            NUMBER_STATE => {
                    if (bracket_num > 0) {
                        if (randint(1, 3) == 1) {
                            state = CLOSE_BRACKET_STATE;
                        } else {
                            state = OPERATOR_STATE;
                        }
                    }
                    else {
                        state = OPERATOR_STATE;
                    }
                    print!("{}", get_number());
                },

            OPERATOR_STATE => {
                    state = *rnd.choose(&OPEN_BRACKET_STATE_ARRAY).unwrap();
                    print!(" {} ", get_operator());
                }
            _ => print!("MORE! FAIL! {}", state),
        }
    }

    // finalize

    if (state == OPERATOR_STATE)
    {
        print!(" {} ", get_operator());
        state = NUMBER_STATE;
    }
    if (state == OPEN_BRACKET_STATE) {
        state = NUMBER_STATE;
    }
    if (state == NUMBER_STATE) {
        print!("{}", get_number());
    }
    if (bracket_num > 0) {
        for i in 0 .. bracket_num {
            print!("{}", CLOSE_BRACKET);
        }
    }
}

fn main() {
    let mut args: Vec<String> = Vec::new();
    for a in  std::env::args() {
        args.push(a);
    }

    let mut max_symbol_count: u64 = 1024;

    if (args.len() > 1) {
        let value = args.last().unwrap().parse::<u64>();
        match value {
            Ok(n) => max_symbol_count = n,
            Err(n) => panic!("Can't parse to int with reason '{}'", n),
        }
    }
    generate_infix(max_symbol_count);
}
