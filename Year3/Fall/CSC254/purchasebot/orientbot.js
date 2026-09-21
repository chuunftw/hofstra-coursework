const OrientDB = require('orientjs');


const ORDER_INTERVAL = 5000; //5 seconds 


function getRandomElement(arr) {
  return arr[Math.floor(Math.random() * arr.length)];
}


function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

// formatting date
function formatDateForOrientDB(date) {
  const pad = (num) => String(num).padStart(2, '0');
  const year = date.getFullYear();
  const month = pad(date.getMonth() + 1);
  const day = pad(date.getDate());
  const hours = pad(date.getHours());
  const minutes = pad(date.getMinutes());
  const seconds = pad(date.getSeconds());
  return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
}

async function createRandomOrder(db, products, customers) {
  try {
    console.log('Creating new order...');
    //choose rand customer 
    const customer = getRandomElement(customers);

    // pick 1-3 random products
    const numProductTypes = getRandomInt(1, 3);
    const selectedProducts = [];
    const usedProductIds = new Set();

    // choose unique products 
    while (selectedProducts.length < numProductTypes) {
      const product = getRandomElement(products);
      if (!usedProductIds.has(product['@rid'].toString())) {
        usedProductIds.add(product['@rid'].toString());
        const quantity = getRandomInt(1, 1000);
        selectedProducts.push({
          product: product,
          quantity: quantity,
          subtotal: product.price * quantity
        });
      }
    }

    // calc total price
    const totalPrice = selectedProducts.reduce((sum, item) => sum + item.subtotal, 0);

    // Create the order
    const orderDate = formatDateForOrientDB(new Date());
    const orderResult = await db.query(
      `INSERT INTO Order SET customer = ?, orderDate = ?, totalPrice = ?, status = 'completed'`,
      {
        params: [customer['@rid'], orderDate, totalPrice]
      }
    ).all();

    const orderId = orderResult[0]['@rid'];

    // create order items
    for (const item of selectedProducts) {
      await db.query(
        `INSERT INTO OrderItem SET order = ?, product = ?, quantity = ?, price = ?, subtotal = ?`,
        {
          params: [orderId, item.product['@rid'], item.quantity, item.product.price, item.subtotal]
        }
      ).all();
    }

    // log the created order
    console.log('\n=== New Order Created ===');
    console.log(`Order ID: ${orderId}`);
    console.log(`Customer: ${customer.name} (${customer.email})`);
    console.log(`Order Date: ${orderDate}`);
    console.log('Products:');
    selectedProducts.forEach(item => {
      console.log(`  - ${item.product.name} x${item.quantity} @ $${item.product.price} = $${item.subtotal.toFixed(2)}`);
    });
    console.log(`Total: $${totalPrice.toFixed(2)}`);
    console.log('========================\n');

  } catch (err) {
    console.error('Error creating order:', err.message);
    console.error('Full error:', err);
  }
}

async function main() {
  const server = OrientDB({
    host: "localhost",
    port: 2424,
    username: "root",
    password: "wigwomm",
    useToken: true 
  });

  const db = server.use({
    name: "demodb",
    username: "root",
    password: "wigwomm"
  });

  try {
    console.log('Connecting to OrientDB...');

  
    const products = await db.query("SELECT FROM Product").all();
    console.log(`Loaded ${products.length} products`);


    const customers = await db.query("SELECT FROM Customer").all();
    console.log(`Loaded ${customers.length} customers`);

    if (products.length === 0 || customers.length === 0) {
      console.error('Error: Database must have products and customers!');
      process.exit(1);
    }

    console.log(`\nStarting order bot - creating orders every ${ORDER_INTERVAL/1000} seconds`);
    console.log('Press Ctrl+C to stop\n');

    // Create first order immediately
    await createRandomOrder(db, products, customers);

    // Then create orders at regular intervals
    setInterval(async () => {
      await createRandomOrder(db, products, customers);
    }, ORDER_INTERVAL);

  } catch (err) {
    console.error("Error:", err);
    db.close();
    server.close();
    process.exit(1);
  }
}

// Handle graceful shutdown
process.on('SIGINT', () => {
  console.log('\nClosing down');
  process.exit(0);
});

main();
