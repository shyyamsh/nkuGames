import { Canvas, useFrame } from '@react-three/fiber'
import * as React from 'react'
import { useRef } from 'react'
import * as THREE from 'three'

// A simple rotating cube that can be reused in the home page.
const RotatingCube = (props: any) => {
  const mesh = useRef<THREE.Mesh | null>(null)
  useFrame(() => {
    if (mesh.current) {
      mesh.current.rotation.x += 0.01
      mesh.current.rotation.y += 0.015
    }
  })
    // Use React.createElement to avoid JSX type errors for Three.js primitives
    return React.createElement(
      'mesh',
      { ref: mesh, ...props },
      React.createElement('boxGeometry', { args: [1, 1, 1] }),
      React.createElement('meshStandardMaterial', { color: '#4caf50' })
    )
}

export default function ThreeScene() {
    return React.createElement(
      Canvas,
      { style: { width: '100%', height: '300px' }, camera: { position: [0, 0, 5] } },
      React.createElement('ambientLight', { intensity: 0.5 }),
      React.createElement('pointLight', { position: [10, 10, 10] }),
      React.createElement(RotatingCube, { position: [0, 0, 0] })
    )
}
