import Head from 'next/head'
import Image from 'next/image'
import styles from '../styles/Home.module.css'

export default function Home() {
  return (
    <div className={styles.container}>
      <Head>
        <title>NKU Games</title>
        <meta name="description" content="Multiplayer games portal" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <main className={styles.main}>
        <h1 className={styles.title}>Welcome to NKU Games</h1>
        <p className={styles.description}>Your multiplayer gaming hub.</p>
      </main>
    </div>
  )
}
