type
AllocBlock_ptr =  ^AllocBlock;
AllocBlock = record;
    prev: AllocBlock_ptr;
    next : AllocBlock_ptr;
    item_list : AllocBlock_ptr;
    size : integer;
    /*struct AllocItem data[1];*/
end;
