import Image from 'next/image'
import styles from '../styles/GameCard.module.css'

export interface GameCardProps {
  title: string
  description: string
  imageUrl: string
}

export default function GameCard({ title, description, imageUrl }: GameCardProps) {
  return (
    <div className={styles.card}>
      <Image src={imageUrl} alt={title} width={300} height={200} className={styles.image} />
      <h3>{title}</h3>
      <p>{description}</p>
    </div>
  )
}
