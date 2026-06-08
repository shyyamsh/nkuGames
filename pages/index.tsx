import Head from 'next/head'
import Image from 'next/image'
import Link from 'next/link'
import NavBar from '../components/NavBar'
import styles from '../styles/Home.module.css'
import ThreeScene from '../components/ThreeScene'
import GameCard, { GameCardProps } from '../components/GameCard'

export default function Home() {
    const sampleGames: GameCardProps[] = [
      // Classic C++ games
      {
        title: 'Tetris',
        description: 'Falling blocks game. ',
        imageUrl: '/images/tetris.png',
        link: '/Tetris'
      },
      {
        title: 'Retro Snake',
        description: 'Classic Retro Snake.',
        imageUrl: '/images/snake.png',
        link: '/RetroSnake'
      },
      {
        title: 'MineSweeper',
        description: 'Mine Sweeper puzzle.',
        imageUrl: '/images/minesweeper.png',
        link: '/MineSweeper'
      }
    ];
  return (
    <div className={styles.container}>
      <Head>
        <title>NKU Games</title>
        <meta name="description" content="Multiplayer games portal" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <NavBar />
      <main className={styles.main}>
        <ThreeScene />
        <h1 className={styles.title}>Welcome to NKU Games</h1>
        <p className={styles.description}>Your Gaming Hub.</p>
        <section className={styles.gameGrid}>
          {sampleGames.map((game) => (
            <GameCard key={game.title} {...game} />
          ))}
        </section>
      </main>
    </div>
  )
}
