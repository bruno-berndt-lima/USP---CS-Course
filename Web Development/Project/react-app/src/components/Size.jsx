import React from 'react';

const Size = ({product}) => {
    // Ordena os tamanhos para organizar o select
    const availableSizes = product.sizes.sort((a, b) => {
        return a.size - b.size
    }).filter(e => {
        if(e.stock > 0) return e 
    })

    return (
        <>            
            {availableSizes.map(e => {
                return <option key={e.size} value={e.size}>{e.size}</option>
            })}
        </>  
    );
}
 
export default Size;