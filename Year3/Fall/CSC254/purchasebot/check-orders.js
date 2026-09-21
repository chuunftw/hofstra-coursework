const OrientDB = require('orientjs');

async function checkOrders() {
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
    console.log('Checking database for orders...\n');

    // Count total orders
    const orderCount = await db.query("SELECT count(*) as count FROM Order").all();
    console.log(`Total Orders: ${orderCount[0].count}`);

    // Get recent orders
    const recentOrders = await db.query("SELECT FROM Order ORDER BY orderDate DESC LIMIT 5").all();

    console.log('\nRecent Orders:');
    console.log('='.repeat(80));

    for (const order of recentOrders) {
      console.log(`\nOrder ${order['@rid']}`);
      console.log(`  Date: ${order.orderDate}`);
      console.log(`  Total: $${order.totalPrice ? order.totalPrice.toFixed(2) : 'N/A'}`);
      console.log(`  Status: ${order.status}`);

      // Get order items
      const items = await db.query(
        "SELECT FROM OrderItem WHERE order = ?",
        { params: [order['@rid']] }
      ).all();

      if (items.length > 0) {
        console.log(`  Items (${items.length}):`);
        for (const item of items) {
          console.log(`    - Quantity: ${item.quantity}, Price: $${item.price}, Subtotal: $${item.subtotal}`);
        }
      }
    }

    console.log('\n' + '='.repeat(80));

  } catch (err) {
    console.error("Error:", err.message);
  } finally {
    db.close();
    server.close();
  }
}

checkOrders();
